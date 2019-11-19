#include "../IPTestAdministrator.h"

#include <gtest/gtest.h>
#include <core/core.h>
#include <websocket/websocket.h>

namespace WPEFramework {
namespace Tests {

namespace StreamJsonTest {
    typedef enum {
        ExecuteShell,
        WiFiSettings,
        FanControl,
        PlayerControl
    } CommandType;

    class Parameters : public Core::JSON::Container {
    private:
        Parameters(const Parameters&);
        Parameters& operator=(const Parameters&);

    public:
        Parameters()
        {
            Add(_T("speed"), &Speed);
            Add(_T("duration"), &Duration);
            Add(_T("command"), &Command);
            Add(_T("settings"), &Settings);
        }
        ~Parameters()
        {
        }

    public:
        Core::JSON::OctSInt16 Speed;
        Core::JSON::DecUInt16 Duration;
        Core::JSON::EnumType<CommandType> Command;
        Core::JSON::ArrayType<Core::JSON::DecUInt16> Settings;
    };

    class Command : public Core::JSON::Container {
    private:
        Command(const Command&);
        Command& operator=(const Command&);

    public:
        Command()
        {
            Add(_T("id"), &Identifier);
            Add(_T("name"), &Name);
            Add(_T("baseAddress"), &BaseAddress);
            Add(_T("trickFlag"), &TrickFlag);
            Add(_T("parameters"), &Params);
        }
        ~Command()
        {
        }
    public:
        Core::JSON::DecUInt32 Identifier;
        Core::JSON::String Name;
        Core::JSON::HexUInt32 BaseAddress;
        Core::JSON::Boolean TrickFlag;
        Parameters Params;
    };

    const TCHAR* g_connector = "/tmp/wpestreamjson0";
    bool g_done = false;
} // StreamJsonTest

    class JSONObjectFactory : public Core::ProxyPoolType<StreamJsonTest::Command> {
    private:
        JSONObjectFactory() = delete;
        JSONObjectFactory(const JSONObjectFactory&) = delete;
        JSONObjectFactory& operator= (const JSONObjectFactory&) = delete;

    public:
        JSONObjectFactory(const uint32_t number) : Core::ProxyPoolType<StreamJsonTest::Command>(number) {
        }
        virtual ~JSONObjectFactory() {
        }

    public:
        Core::ProxyType<Core::JSON::IElement> Element(const string&) {
            return (Core::proxy_cast<Core::JSON::IElement>(Core::ProxyPoolType<StreamJsonTest::Command>::Element()));
        }
    };

    template<typename INTERFACE>
    class JSONConnector : public Core::StreamJSONType<Core::SocketStream, JSONObjectFactory&, INTERFACE> {
    private:
        typedef Core::StreamJSONType<Core::SocketStream, JSONObjectFactory&, INTERFACE> BaseClass;

        JSONConnector();
        JSONConnector(const JSONConnector& copy);
        JSONConnector& operator=(const JSONConnector&);

    public:
        JSONConnector(const Core::NodeId& remoteNode)
            : BaseClass(5, _objectFactory, false, remoteNode.AnyInterface(), remoteNode, 1024, 1024)
            , _serverSocket(false)
            , _dataPending(false, false)
            , _objectFactory(1)
        {
        }
        JSONConnector(const SOCKET& connector, const Core::NodeId& remoteId, Core::SocketServerType<JSONConnector<INTERFACE>>*)
            : BaseClass(5, _objectFactory, false, connector, remoteId, 1024, 1024)
            , _serverSocket(true)
            , _dataPending(false, false)
            , _objectFactory(1)
        {
        }
        virtual ~JSONConnector()
        {
        }

    public:
        virtual void Received(Core::ProxyType<Core::JSON::IElement>& newElement)
        {
            string textElement;
            newElement->ToString(textElement);

            if (_serverSocket)
                this->Submit(newElement);
            else {
                _dataReceived = textElement;
                _dataPending.Unlock();
            }
        }
        virtual void Send(Core::ProxyType<Core::JSON::IElement>& newElement)
        {
        }
        virtual void StateChange()
        {
            if (this->IsOpen()) {
                if (_serverSocket)
                    StreamJsonTest::g_done = true;
            }
        }
        virtual bool IsIdle() const
        {
            return (true);
        }
        int Wait() const
        {
            return _dataPending.Lock();
        }
        void Retrieve(string& text)
        {
            text = _dataReceived;
            _dataReceived.clear();
        }
    private:
        bool _serverSocket;
        string _dataReceived;
        mutable Core::Event _dataPending;
        JSONObjectFactory _objectFactory;
    };

    TEST(Core_Socket, StreamJSON)
    {
        IPTestAdministrator::OtherSideMain otherSide = [](IPTestAdministrator & testAdmin) {
            Core::SocketServerType<JSONConnector<Core::JSON::IElement>> jsonSocketServer(Core::NodeId(StreamJsonTest::g_connector));
            jsonSocketServer.Open(Core::infinite);
            testAdmin.Sync("setup server");
            while(!StreamJsonTest::g_done);
            testAdmin.Sync("server open");
            testAdmin.Sync("client done");
        };

        IPTestAdministrator testAdmin(otherSide);
        testAdmin.Sync("setup server");
        {
            Core::ProxyType<StreamJsonTest::Command> sendObject = Core::ProxyType<StreamJsonTest::Command>::Create();
            sendObject->Identifier = 1;
            sendObject->Name = _T("TestCase");
            sendObject->Params.Duration = 100;
            std::string sendString;
            sendObject->ToString(sendString);

            JSONConnector<Core::JSON::IElement> jsonSocketClient(Core::NodeId(StreamJsonTest::g_connector));
            jsonSocketClient.Open(Core::infinite);
            testAdmin.Sync("server open");
            jsonSocketClient.Submit(Core::proxy_cast<Core::JSON::IElement>(sendObject));
            jsonSocketClient.Wait();
            string received;
            jsonSocketClient.Retrieve(received);
            EXPECT_STREQ(sendString.c_str(), received.c_str());
            jsonSocketClient.Close(Core::infinite);
            testAdmin.Sync("client done");
        }
        Core::Singleton::Dispose();
    }
} // Tests

ENUM_CONVERSION_BEGIN(Tests::StreamJsonTest::CommandType)
    { Tests::StreamJsonTest::ExecuteShell, _TXT("ExecuteShell") },
    { Tests::StreamJsonTest::WiFiSettings, _TXT("WiFiSettings") },
    { Tests::StreamJsonTest::FanControl, _TXT("FanControl") },
    { Tests::StreamJsonTest::PlayerControl, _TXT("PlayerControl") },
ENUM_CONVERSION_END(Tests::StreamJsonTest::CommandType)

} // WPEFramework
