# Fender::Network

Fender allows you to create Multiplayer online games using Tcp and Udp connections.

How is that possible ?

## Packet

```c++
struct Packet : futils::IComponent
{
	futils::NetworkAgent target;
	mutils::BinaryData object;
}
```

## System::Network

```c++
class Network : System
{
	Container<mutils::socketThread> clients;
}
```

```c++
void Network::run(float)
{
  for (auto &client: clients)
  {
    mutils::ISocketMessage buffer;
	while (client.read(&buffer) > 0)
    {
		events->send<mutils::ISocketMessage>(buffer); 
    }
  }
  addReaction<NewConnection>([this](futils::IMediatorPacket &pkg){
	auto &connection = futils::Mediator::rebuild<NewConnection>(pkg);
    clients.insert(new SocketThread(connection));
  });
  addReaction<Packet>([this](futils::IMediatorPacket &pkg){
    	auto &packet = futils::Mediator::rebuild<Packet>(pkg);
		auto &target = findTarget(packet.target);
		target.write(packet.object);
  });
}
```

