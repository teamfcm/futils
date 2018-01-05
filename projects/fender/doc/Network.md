# Fender::Network

Fender allows you to create Multiplayer online games using Tcp and Udp connections.

How is that possible ?

## Packet

> Send it through the Events mediator.

```c++
struct Packet : futils::IComponent
{
	mutils::NetworkAgent target;
	mutils::BinaryData object;
};
```

## fender::NetworkSystems::System

```c++
namespace fender::NetworkSystems
{
	class System : futils::ISystem
    {
		public:
			System() {
            addReaction<fender::events::Shutdown>([this](){
            	this->entityManager->removeSystem(name);
            });
            }
    };
}
```



## System::Listener

```c++
namespace fender::NetworkSystems
{
	class Listener : System
	{
		enum States
        {
        	Init = 0,
        	Run
        };
        
        TcpSocket serverSocket;
       
        	void init()
            {
            	phase = Run;
                serverSocket->onConnect([this](TcpSocket &connection){
                	connection.handshake == configFile[handshake];
                	NewConnection nc;
                	nc.connection = connection;
                	this->events->send<NewConnection>(nc);
                });
            }
            
		public:
			void run(float) override
            {
				switch (phase)
					case Init : return init();
					case Run : return ;
            }
	};
}
```

## System::Network

```c++
class Network : NetworkSystem
{
	Container<mutils::SocketThread> clients;
};
```

```c++
void Network::run(float)
{
  for (auto &client: clients)
  {
    mutils::SocketThread::Message buffer;
	while (client.read(&buffer) > 0)
    {
		events->send<mutils::socketThread::Message>(buffer); 
    }
  }
  // A faire dans init :
  addReaction<NewTcpConnection>([this](futils::IMediatorPacket &pkg){
	auto &packet = futils::Mediator::rebuild<NewConnection>(pkg);
    clients.insert(new mutils::SocketThread(packet.connection));
    packet.connection.onDisconnect([this](TcpSocket &connection, mutils::SocketClosed status){
		clients.erase(connection);
		this->events->send<fender::Error>(status.what());
    });
  });
  addReaction<Packet>([this](futils::IMediatorPacket &pkg){
    	auto &packet = futils::Mediator::rebuild<Packet>(pkg);
		auto &target = findTarget(packet.target);
		target.write(packet.object);
  });
}
```

