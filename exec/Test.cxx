
#include "Sentinel.h"

#include <iostream>
#include <cassert>

using namespace Sentinel;


int main( int, char** )
{

  {
    Serializer serialSender;
    Serializer serialReceiver;

    std::cout << "Creating test payload" << std::endl;
    Payload* test_payload = new Payload( 4897, ProtocolCommand::Alive, "Hi there", "Chazz" );

    std::cout << '\n' << test_payload->print() << '\n' << std::endl;

    std::cout << "Serializing" << std::endl;
    serialSender.serialize( test_payload );

    assert( serialSender.bufferEmpty() == false );
    assert( serialSender.errorEmpty() == true );

    std::cout << "Pop buffer" << std::endl;
    Stewardess::Buffer* temp_buffer = serialSender.getBuffer();

    std::cout << "Raw Buffer : " << temp_buffer->getString() << std::endl;

    std::cout << "Deserializing" << std::endl;
    serialReceiver.deserialize( temp_buffer );

    assert( serialReceiver.payloadEmpty() == false );
    assert( serialReceiver.errorEmpty() == true );

    std::cout << "Recovered payload:" << std::endl;

    Payload* new_payload = (Payload*)serialReceiver.getPayload();
    std::cout << '\n' << new_payload->print() << '\n' << std::endl;

    delete test_payload;
    delete temp_buffer;
    delete new_payload;
  }
  std::cout << "\n----------------------------------------------------------------------------------------------------\n" << std::endl;
  {
    Serializer serialSender;
    Serializer serialReceiver;

    std::cout << "Creating test payload" << std::endl;
    Payload* test_payload = new Payload( 42, ProtocolCommand::AuthorizeDeny );

    std::cout << '\n' << test_payload->print() << '\n' << std::endl;

    std::cout << "Serializing" << std::endl;
    serialSender.serialize( test_payload );

    assert( serialSender.bufferEmpty() == false );
    assert( serialSender.errorEmpty() == true );

    std::cout << "Pop buffer" << std::endl;
    Stewardess::Buffer* temp_buffer = serialSender.getBuffer();

    std::cout << "Raw Buffer : " << temp_buffer->getString() << std::endl;

    std::cout << "Deserializing" << std::endl;
    serialReceiver.deserialize( temp_buffer );

    assert( serialReceiver.payloadEmpty() == false );
    assert( serialReceiver.errorEmpty() == true );

    std::cout << "Recovered payload:" << std::endl;

    Payload* new_payload = (Payload*)serialReceiver.getPayload();
    std::cout << '\n' << new_payload->print() << '\n' << std::endl;

    delete test_payload;
    delete temp_buffer;
    delete new_payload;
  }
  std::cout << "\n----------------------------------------------------------------------------------------------------\n" << std::endl;
  {
    Serializer serialSender;
    Serializer serialReceiver;

    std::cout << "Creating test payload" << std::endl;
    Payload* test_payload = new Payload( 9, ProtocolCommand::AuthorizeAccept );

    std::cout << '\n' << test_payload->print() << '\n' << std::endl;

    std::cout << "Serializing" << std::endl;
    serialSender.serialize( test_payload );

    assert( serialSender.bufferEmpty() == false );
    assert( serialSender.errorEmpty() == true );

    std::cout << "Pop buffer" << std::endl;
    Stewardess::Buffer* temp_buffer = serialSender.getBuffer();

    std::cout << "Raw Buffer : " << temp_buffer->getString() << std::endl;

    std::cout << "Deserializing" << std::endl;
    serialReceiver.deserialize( temp_buffer );

    assert( serialReceiver.payloadEmpty() == false );
    assert( serialReceiver.errorEmpty() == true );

    std::cout << "Recovered payload:" << std::endl;

    Payload* new_payload = (Payload*)serialReceiver.getPayload();
    std::cout << '\n' << new_payload->print() << '\n' << std::endl;

    delete test_payload;
    delete temp_buffer;
    delete new_payload;
  }
  std::cout << "\n----------------------------------------------------------------------------------------------------\n" << std::endl;
  {
    Serializer serialSender;
    Serializer serialReceiver;

    std::cout << "Creating test payload" << std::endl;
    Payload* test_payload = new Payload( 0, ProtocolCommand::AuthorizeRequest );
    test_payload->setStaffID( 4 );

    std::cout << '\n' << test_payload->print() << '\n' << std::endl;

    std::cout << "Serializing" << std::endl;
    serialSender.serialize( test_payload );

    assert( serialSender.bufferEmpty() == false );
    assert( serialSender.errorEmpty() == true );

    std::cout << "Pop buffer" << std::endl;
    Stewardess::Buffer* temp_buffer = serialSender.getBuffer();

    std::cout << "Raw Buffer : " << temp_buffer->getString() << std::endl;

    std::cout << "Deserializing" << std::endl;
    serialReceiver.deserialize( temp_buffer );

    assert( serialReceiver.payloadEmpty() == false );
    assert( serialReceiver.errorEmpty() == true );

    std::cout << "Recovered payload:" << std::endl;

    Payload* new_payload = (Payload*)serialReceiver.getPayload();
    std::cout << '\n' << new_payload->print() << '\n' << std::endl;

    delete test_payload;
    delete temp_buffer;
    delete new_payload;
  }
  return 0;
}

