#ifndef CHATGUICLIENT_H
#define CHATGUICLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QMessageBox>
#include <QHostAddress>
#include <cstring>

// ✅ 替换宏定义（关键修复）
static constexpr int MSG_TEXT_SIZE = 128;
static constexpr int MSG_LOGIN = 1;
static constexpr int MSG_CHAT = 2;
static constexpr int MSG_QUIT = 3;

class ChatGuiClient : public QWidget
{
    Q_OBJECT

public:
    explicit ChatGuiClient(QWidget* parent = nullptr);
    ~ChatGuiClient();

private slots:
    void connectToServer();
    void sendChatMessage();
    void readServerMessage();
    void onDisconnected();
    void onSocketError(QAbstractSocket::SocketError socketError);

private:
    struct MSG
    {
        int type;
        char name[20];
        char text[MSG_TEXT_SIZE];

        QByteArray serialize() const
        {
            QByteArray data;
            data.append(reinterpret_cast<const char*>(&type), sizeof(type));
            data.append(name, sizeof(name));
            data.append(text, sizeof(text));
            return data;
        }

        void deserialize(const QByteArray& data)
        {
            int offset = 0;
            if (data.size() < static_cast<int>(sizeof(type) + sizeof(name) + sizeof(text))) {
                return;
            }
            std::memcpy(&type, data.constData() + offset, sizeof(type));
            offset += sizeof(type);
            std::memcpy(name, data.constData() + offset, sizeof(name));
            offset += sizeof(name);
            std::memcpy(text, data.constData() + offset, sizeof(text));
            name[sizeof(name) - 1] = '\0';
            text[sizeof(text) - 1] = '\0';
        }
    };

    void initUi();
    void setConnectedState(bool connected);
    void appendSystemMessage(const QString& message);
    void appendChatMessage(const QString& sender, const QString& message, bool isSelf);
    void sendMsg(int type, const QString& text = QString());

private:
    QTcpSocket* socket;

    QLineEdit* ipEdit;
    QLineEdit* portEdit;
    QLineEdit* nameEdit;
    QPushButton* connectButton;
    QLabel* statusLabel;

    QTextEdit* chatView;
    QLineEdit* messageEdit;
    QPushButton* sendButton;

    QString userName;
    bool connected;
};

#endif