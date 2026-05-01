#include "chatGuiClient.h"

ChatGuiClient::ChatGuiClient(QWidget* parent)
    : QWidget(parent), socket(new QTcpSocket(this)), connected(false)
{
    initUi();

    connect(connectButton, &QPushButton::clicked, this, &ChatGuiClient::connectToServer);
    connect(sendButton, &QPushButton::clicked, this, &ChatGuiClient::sendChatMessage);
    connect(messageEdit, &QLineEdit::returnPressed, this, &ChatGuiClient::sendChatMessage);
    connect(socket, &QTcpSocket::readyRead, this, &ChatGuiClient::readServerMessage);
    connect(socket, &QTcpSocket::disconnected, this, &ChatGuiClient::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
        this, &ChatGuiClient::onSocketError);

    setConnectedState(false);
}

ChatGuiClient::~ChatGuiClient()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        sendMsg(MSG_QUIT, "离开聊天室");
        socket->disconnectFromHost();
    }
}

void ChatGuiClient::initUi()
{
    setWindowTitle("网络聊天室 - 图形客户端");
    resize(760, 540);

    ipEdit = new QLineEdit("127.0.0.1", this);
    portEdit = new QLineEdit("12345", this);
    nameEdit = new QLineEdit("user", this);
    connectButton = new QPushButton("连接", this);
    statusLabel = new QLabel("未连接", this);

    chatView = new QTextEdit(this);
    chatView->setReadOnly(true);

    messageEdit = new QLineEdit(this);
    messageEdit->setPlaceholderText("输入消息，按 Enter 发送...");
    sendButton = new QPushButton("发送", this);

    auto* topLayout = new QHBoxLayout;
    topLayout->addWidget(new QLabel("IP:"));
    topLayout->addWidget(ipEdit);
    topLayout->addWidget(new QLabel("端口:"));
    topLayout->addWidget(portEdit);
    topLayout->addWidget(new QLabel("昵称:"));
    topLayout->addWidget(nameEdit);
    topLayout->addWidget(connectButton);
    topLayout->addWidget(statusLabel);

    auto* bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(messageEdit);
    bottomLayout->addWidget(sendButton);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(chatView);
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);

    setStyleSheet(R"(
        QWidget {
            background-color: #f4f6fb;
            font-family: "Microsoft YaHei", "Arial";
            font-size: 14px;
        }
        QLineEdit {
            background: white;
            border: 1px solid #d6dbea;
            border-radius: 8px;
            padding: 8px 10px;
        }
        QTextEdit {
            background: white;
            border: 1px solid #d6dbea;
            border-radius: 12px;
            padding: 10px;
        }
        QPushButton {
            background-color: #4f7cff;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #3f6bed;
        }
        QPushButton:disabled {
            background-color: #aab4d4;
        }
        QLabel {
            color: #30364a;
        }
    )");
}

void ChatGuiClient::connectToServer()
{
    if (connected) {
        sendMsg(MSG_QUIT, "离开聊天室");
        socket->disconnectFromHost();
        return;
    }

    userName = nameEdit->text().trimmed();

    if (ipEdit->text().trimmed().isEmpty() ||
        portEdit->text().trimmed().isEmpty() ||
        userName.isEmpty()) {
        QMessageBox::warning(this, "提示", "请填写 IP、端口和昵称");
        return;
    }

    socket->connectToHost(ipEdit->text().trimmed(),
        portEdit->text().trimmed().toUShort());

    if (!socket->waitForConnected(3000)) {
        QMessageBox::critical(this, "连接失败", socket->errorString());
        return;
    }

    setConnectedState(true);
    appendSystemMessage("已连接服务器");
    sendMsg(MSG_LOGIN, "加入聊天室");
}

void ChatGuiClient::sendChatMessage()
{
    QString text = messageEdit->text().trimmed();

    if (!connected || text.isEmpty()) {
        return;
    }

    sendMsg(MSG_CHAT, text);
    appendChatMessage(userName, text, true);
    messageEdit->clear();
}

void ChatGuiClient::readServerMessage()
{
    const int frameSize = sizeof(int) + 20 + MSG_TEXT_SIZE;

    while (socket->bytesAvailable() >= frameSize) {
        QByteArray data = socket->read(frameSize);

        MSG msg;
        std::memset(&msg, 0, sizeof(msg));
        msg.deserialize(data);

        QString sender = QString::fromLocal8Bit(msg.name).trimmed();
        QString text = QString::fromLocal8Bit(msg.text).trimmed();

        if (msg.type == MSG_LOGIN) {
            appendSystemMessage(sender + " 加入聊天室");
        }
        else if (msg.type == MSG_CHAT) {
            appendChatMessage(sender, text, false);
        }
        else if (msg.type == MSG_QUIT) {
            appendSystemMessage(sender + " 离开聊天室");
        }
    }
}

void ChatGuiClient::onDisconnected()
{
    if (connected) {
        appendSystemMessage("服务器连接已断开");
    }

    setConnectedState(false);
}

void ChatGuiClient::onSocketError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);

    if (socket->state() != QAbstractSocket::ConnectedState) {
        setConnectedState(false);
    }
}

void ChatGuiClient::setConnectedState(bool state)
{
    connected = state;

    connectButton->setText(connected ? "断开" : "连接");
    statusLabel->setText(connected ? "已连接" : "未连接");

    messageEdit->setEnabled(connected);
    sendButton->setEnabled(connected);

    ipEdit->setEnabled(!connected);
    portEdit->setEnabled(!connected);
    nameEdit->setEnabled(!connected);
}

void ChatGuiClient::appendSystemMessage(const QString& message)
{
    QString time = QDateTime::currentDateTime().toString("HH:mm:ss");

    chatView->append(
        QString("<p style='text-align:center;color:#8a91a8;'>[%1] %2</p>")
        .arg(time, message.toHtmlEscaped())
    );
}

void ChatGuiClient::appendChatMessage(const QString& sender,
    const QString& message,
    bool isSelf)
{
    QString time = QDateTime::currentDateTime().toString("HH:mm:ss");
    QString align = isSelf ? "right" : "left";
    QString bg = isSelf ? "#dce7ff" : "#eef1f8";
    QString nameColor = isSelf ? "#315bdc" : "#30364a";

    chatView->append(QString(
        "<div style='text-align:%1; margin:8px 0;'>"
        "<span style='color:%2;font-size:12px;'>%3 %4</span><br>"
        "<span style='display:inline-block;background:%5;border-radius:10px;"
        "padding:8px 12px;max-width:70%;'>%6</span>"
        "</div>")
        .arg(align,
            nameColor,
            sender.toHtmlEscaped(),
            time,
            bg,
            message.toHtmlEscaped()));
}

void ChatGuiClient::sendMsg(int type, const QString& text)
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        return;
    }

    MSG msg;
    std::memset(&msg, 0, sizeof(msg));
    msg.type = type;

    QByteArray nameBytes = userName.toLocal8Bit();
    QByteArray textBytes = text.toLocal8Bit();

    std::strncpy(msg.name, nameBytes.constData(), sizeof(msg.name) - 1);
    std::strncpy(msg.text, textBytes.constData(), sizeof(msg.text) - 1);

    QByteArray data = msg.serialize();
    socket->write(data);
    socket->flush();
}