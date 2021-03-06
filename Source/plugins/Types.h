#pragma once
#include "IPlugin.h"
#include "Module.h"

namespace WPEFramework {
namespace RPC {
    template <typename HANDLER, Core::ProxyType<RPC::IIPCServer> ENGINE() = DefaultInvokeServer>
    class PluginMonitorType {
    private:
        enum state : uint8_t {
            UNKNOWN,
            DEACTIVATED,
            ACTIVATED
        };
        class Sink : public PluginHost::IPlugin::INotification {
        public:
            Sink() = delete;
            Sink(const Sink&) = delete;
            Sink& operator=(const Sink&) = delete;

            Sink(PluginMonitorType<HANDLER, ENGINE>& parent)
                : _parent(parent)
            {
            }
            ~Sink() override = default;

        public:
            void StateChange(PluginHost::IShell* plugin, const string& name) override
            {
                _parent.StateChange(plugin, name);
            }
            void Dispatch()
            {
                _parent.Dispatch();
            }

            BEGIN_INTERFACE_MAP(Sink)
            INTERFACE_ENTRY(PluginHost::IPlugin::INotification)
            END_INTERFACE_MAP

        private:
            PluginMonitorType<HANDLER, ENGINE>& _parent;
        };

    public:
        PluginMonitorType() = delete;
        PluginMonitorType(const PluginMonitorType<HANDLER, ENGINE>&) = delete;
        PluginMonitorType<HANDLER, ENGINE>& operator=(const PluginMonitorType<HANDLER, ENGINE>&) = delete;

        template <typename... Args>
        PluginMonitorType(Args&&... args)
            : _adminLock()
            , _reporter(std::forward<Args>(args)...)
            , _callsign()
            , _node()
            , _sink(*this)
            , _designated(nullptr)
            , _controller(nullptr)
            , _state(UNKNOWN)
            , _administrator()
        {
        }
        ~PluginMonitorType()
        {
            Close(Core::infinite);
        }

        using controllerInterface = PluginHost::IShell;

    public:
        uint32_t Open(const uint32_t waitTime, const Core::NodeId& node, const string& callsign)
        {

            _adminLock.Lock();

            ASSERT(_controller == nullptr);

            if (_controller != nullptr) {
                _adminLock.Unlock();
            } else {
                _administrator.Aquire(waitTime, node, _T(""), ~0, _controller);

                if (_controller == nullptr) {
                    _adminLock.Unlock();
                } else {
                    _node = node;
                    _callsign = callsign;

                    _adminLock.Unlock();

                    ASSERT(_state == state::UNKNOWN);

                    _controller->Register(&_sink);

                    _adminLock.Lock();

                    _state = state::DEACTIVATED;

                    _adminLock.Unlock();

                    Reevaluate();
                }
            }

            return (_controller != nullptr ? Core::ERROR_NONE : Core::ERROR_UNAVAILABLE);
        }
        uint32_t Close(const uint32_t waitTime)
        {
            _adminLock.Lock();
            if (_controller != nullptr) {
                _controller->Unregister(&_sink);
                if (_state == state::ACTIVATED) {
                    _reporter.Deactivated(nullptr);
                }
                _controller->Release();
                _controller = nullptr;
            }
            _state = state::UNKNOWN;
            _adminLock.Unlock();
            return (Core::ERROR_NONE);
        }
        template <typename INTERFACE>
        INTERFACE* Aquire(const uint32_t waitTime, const Core::NodeId& nodeId, const string className, const uint32_t version = ~0)
        {
            return (_administrator.CommunicatorClient::Aquire<INTERFACE>(waitTime, nodeId, className, version));
        }
        inline void Submit(const Core::ProxyType<Core::IDispatch>& job)
        {
            _administrator.Engine().Submit(job);
        }

    private:
        void Reevaluate()
        {
            if (_designated != nullptr) {

                PluginHost::IShell::state current = _designated->State();

                if (current == PluginHost::IShell::ACTIVATED) {
                    _reporter.Activated(_designated);
                    _adminLock.Lock();
                    _state = state::ACTIVATED;
                    _adminLock.Unlock();
                } else if (current == PluginHost::IShell::DEACTIVATION) {
                    if (_state == state::ACTIVATED) {
                        _reporter.Deactivated(_designated);
                    }
                    _adminLock.Lock();
                    _state = state::DEACTIVATED;
                    _adminLock.Unlock();
                }
                _designated->Release();
                _designated = nullptr;
            }
        }
        void StateChange(PluginHost::IShell* plugin, const string& callsign)
        {
            if (callsign == _callsign) {
                _adminLock.Lock();

                if (_state != state::UNKNOWN) {

                    PluginHost::IShell::state current = plugin->State();
                    if (current == PluginHost::IShell::ACTIVATED) {
                        _reporter.Activated(plugin);
                        _state = state::ACTIVATED;
                    } else if (current == PluginHost::IShell::DEACTIVATION) {
                        if (_state == state::ACTIVATED) {
                            _reporter.Deactivated(plugin);
                        }
                        _state = state::DEACTIVATED;
                    }

                } else if (_designated == nullptr) {
                    _designated = plugin;
                    _designated->AddRef();
                }

                _adminLock.Unlock();
            }
        }

    private:
        Core::CriticalSection _adminLock;
        HANDLER _reporter;
        string _callsign;
        Core::NodeId _node;
        Core::Sink<Sink> _sink;
        PluginHost::IShell* _designated;
        PluginHost::IShell* _controller;
        state _state;
        ConnectorType<ENGINE> _administrator;
    };

    template <typename INTERFACE, Core::ProxyType<RPC::IIPCServer> ENGINE() = DefaultInvokeServer>
    class SmartInterfaceType {
    public:
#ifdef __WINDOWS__
#pragma warning(disable : 4355)
#endif
        SmartInterfaceType()
            : _adminLock()
            , _monitor(*this)
            , _smartType(nullptr)
        {
        }
#ifdef __WINDOWS__
#pragma warning(default : 4355)
#endif

        virtual ~SmartInterfaceType()
        {
            Close(Core::infinite);
        }

    public:
        inline bool IsOperational() const
        {
            return (_smartType != nullptr);
        }
        uint32_t Open(const uint32_t waitTime, const Core::NodeId& node, const string& callsign)
        {
            return (_monitor.Open(waitTime, node, callsign));
        }
        uint32_t Close(const uint32_t waitTime)
        {
            return (_monitor.Close(waitTime));
        }

        // IMPORTANT NOTE:
        // If you aquire the interface here, take action on the interface and release it. Do not maintain/stash it
        // since the interface might require to be dropped in the mean time.
        // So usage on the interface should be deterministic and short !!!
        INTERFACE* Interface()
        {
            Core::SafeSyncType<Core::CriticalSection> lock(_adminLock);
            INTERFACE* result = _smartType;

            if (result != nullptr) {
                result->AddRef();
            }

            return (result);
        }
        const INTERFACE* Interface() const
        {
            Core::SafeSyncType<Core::CriticalSection> lock(_adminLock);
            const INTERFACE* result = _smartType;

            if (result != nullptr) {
                result->AddRef();
            }

            return (result);
        }

        // Allow a derived class to take action on a new interface, or almost dissapeared interface..
        virtual void Operational(const bool upAndRunning)
        {
        }

    private:
        friend class PluginMonitorType<SmartInterfaceType<INTERFACE, ENGINE>&, ENGINE>;
        void Activated(PluginHost::IShell* plugin)
        {
            ASSERT(plugin != nullptr);
            _adminLock.Lock();
            DropInterface();
            _smartType = plugin->QueryInterface<INTERFACE>();
            _adminLock.Unlock();
            Operational(true);
        }
        void Deactivated(PluginHost::IShell* /* plugin */)
        {
            Operational(false);
            _adminLock.Lock();
            DropInterface();
            _adminLock.Unlock();
        }
        void DropInterface()
        {
            if (_smartType != nullptr) {
                _smartType->Release();
                _smartType = nullptr;
            }
        }

    private:
        mutable Core::CriticalSection _adminLock;
        PluginMonitorType<SmartInterfaceType<INTERFACE, ENGINE>&, ENGINE> _monitor;
        INTERFACE* _smartType;
    };
}
}
