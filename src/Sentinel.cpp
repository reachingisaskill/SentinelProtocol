
#include "Sentinel.h"

using Stewardess::Buffer;


namespace Sentinel
{

//////////////////////////////////////////////////////////////////////////////////////////////////// 
  // Static variables (unnamed namespace)
  namespace
  {
////////// // Protocal command names
    const char* const ProtocolCommandNames[ ProtocolCommandSize ] = 
    {
      "null",
      "alive",
      "acknowledge",
      "deny",
      "request",
      "update",
      "event",
      "authorize_request",
      "authorize_accept",
      "authorize_deny"
    };


////////// // Parsing constants
  // Chracter to signal start of header
  const char StartCharacter = 1;

  // Chracter to signal separation of fields
  const char SeparationCharacter = 30;

  // Chracter to signal end of transmission
  const char EndCharacter = 4;

  }


////////////////////////////////////////////////////////////////////////////////////////////////////
  // Protocol function definitions

  ProtocolCommand getCommandFromName( std::string& name )
  {
    for ( size_t i = 0; i < ProtocolCommandSize; ++i )
    {
      if ( name.compare( ProtocolCommandNames[i] ) == 0 )
        return static_cast<ProtocolCommand>( i );
    }
    return ProtocolCommand::Null;
  }


  const char* getNameFromCommand( ProtocolCommand command )
  {
    return ProtocolCommandNames[ static_cast<size_t>( command ) ];
  }


////////////////////////////////////////////////////////////////////////////////////////////////////
  // Error string definitions
  namespace
  {
    const char* ErrorMalformedPayload = "Payload was not well formed.";
  }


////////////////////////////////////////////////////////////////////////////////////////////////////
  // Payload member function definitions

  Payload::Payload() :
    Stewardess::Payload(),
    _identifier( 0 ),
    _command(),
    _data1(),
    _data2()
  {
    INFO_LOG( "Payload::Payload", "Payload created." );
  }



  Payload::Payload( Stewardess::UniqueID id, ProtocolCommand command ) :
    Stewardess::Payload(),
    _identifier( id ),
    _command( command ),
    _data1( "" ),
    _data2( "" )
  {
    INFO_LOG( "Payload::Payload", "Payload created." );
  }


  Payload::Payload( Stewardess::UniqueID id, ProtocolCommand command, std::string d1, std::string d2 ) :
    Stewardess::Payload(),
    _identifier( id ),
    _command( command ),
    _data1( d1 ),
    _data2( d2 )
  {
    INFO_LOG( "Payload::Payload", "Payload created." );
  }


  Payload::~Payload()
  {
    INFO_LOG( "Payload::Payload", "Payload destroyed." );
  }


  Stewardess::UniqueID Payload::getStaffID() const
  {
    Stewardess::UniqueID temp = std::atoll( _data1.c_str() );
    return temp;
  }


  void Payload::setStaffID( Stewardess::UniqueID sid )
  {
    _data1 = std::to_string( sid );
  }


  std::string Payload::print() const
  {
    std::stringstream ss;
    ss << "Device: " << _identifier << " : " << getNameFromCommand( _command ) << " : " << _data1 << " -- " << _data2;
    return ss.str();
  }

  
////////////////////////////////////////////////////////////////////////////////////////////////////
  // Serializer member function definitions

  Serializer::Serializer() :
    Stewardess::Serializer()
  {
    INFO_LOG( "Serializer::Serializer", "Serialzer created." );
  }


  Serializer::~Serializer()
  {
    INFO_LOG( "Serializer::Serializer", "Serialzer destroyed." );
  }


  void Serializer::serialize( const Stewardess::Payload* p )
  {
    Payload* payload = (Payload*)p;

    std::string identifier_name = std::to_string( payload->_identifier );
    std::string command_name = getNameFromCommand( payload->_command );

    // Add separation and start/finish characters between the sections
    size_t buffer_size = identifier_name.size() + command_name.size() + payload->_data1.size() + payload->_data2.size() + 5;
    Buffer* buffer = new Buffer( buffer_size );

    buffer->push( StartCharacter );
    buffer->push( identifier_name );
    buffer->push( SeparationCharacter );
    buffer->push( command_name );
    buffer->push( SeparationCharacter );
    buffer->push( payload->_data1 );
    buffer->push( SeparationCharacter );
    buffer->push( payload->_data2 );
    buffer->push( EndCharacter );

    // Push it to the write queue
    this->pushBuffer( buffer );
  }


  void Serializer::deserialize( const Buffer* buffer )
  {
    Buffer::Iterator iterator = buffer->getIterator();

    Payload* current_payload = nullptr;
    std::string current_string;

    while ( iterator )
    {
      if ( current_payload == nullptr ) // Start a new one
      {
  //////////////////// // Find the start
        while ( iterator )
        {
          if ( *iterator == StartCharacter )
          {
            current_payload = new Payload();
            break;
          }
          ++iterator;
        }
      }

      if ( ! iterator )
      {
        delete current_payload;
        this->pushError( ErrorMalformedPayload );
        return;
      }
      else
      {
        ++iterator;
      }

  //////////////////// // Load the ID
      while ( iterator && *iterator != SeparationCharacter )
      {
        current_string.push_back( *iterator );
        ++iterator;
      }

      if ( ! iterator )
      {
        delete current_payload;
        current_payload = nullptr;
        this->pushError( ErrorMalformedPayload );
        return;
      }
      else
      {
        current_payload->_identifier = std::atol( current_string.c_str() );
        current_string.clear();
        ++iterator;
      }

  //////////////////// // Load the Command
      while ( iterator && *iterator != SeparationCharacter )
      {
        current_string.push_back( *iterator );
        ++iterator;
      }

      if ( ! iterator )
      {
        delete current_payload;
        current_payload = nullptr;
        this->pushError( ErrorMalformedPayload );
        return;
      }
      else
      {
        current_payload->_command = getCommandFromName( current_string );
        current_string.clear();
        ++iterator;
      }

  //////////////////// // Load the Data
      while ( iterator && *iterator != SeparationCharacter )
      {
        current_payload->_data1.push_back( *iterator );
        ++iterator;
      }

      if ( ! iterator )
      {
        delete current_payload;
        current_payload = nullptr;
        this->pushError( ErrorMalformedPayload );
        return;
      }
      else
      {
        ++iterator;
      }

  //////////////////// // Load the other Data
      while ( iterator && *iterator != EndCharacter )
      {
        current_payload->_data2.push_back( *iterator );
        ++iterator;
      }

      if ( ! iterator )
      {
        delete current_payload;
        current_payload = nullptr;
        this->pushError( ErrorMalformedPayload );
        return;
      }
      else
      {
        this->pushPayload( current_payload );
        current_payload = nullptr;
        ++iterator;
      }
    }
  }

}

