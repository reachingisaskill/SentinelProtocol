
#ifndef SENTINEL_PROTOCOL_LIBRARY_H_
#define SENTINEL_PROTOCOL_LIBRARY_H_

#include "Stewardess.h"


namespace Sentinel
{
  ////////////////////////////////////////////////////////////////////////////////
  // Definitions for the protocol

  const size_t ProtocolCommandSize = 9;

  enum class ProtocolCommand
  {
    Null,
    Alive,
    Connected,
    Request,
    Update,
    Event,
    AuthorizeRequest,
    AuthorizeAccept,
    AuthorizeDeny
  };


////////////////////////////////////////////////////////////////////////////////
  // Protocol function declarations

  // Return the command id from the string represetation
  ProtocolCommand getCommandFromName( std::string& );

  // Return the string representation from the command id
  const char* getNameFromCommand( ProtocolCommand );


  ////////////////////////////////////////////////////////////////////////////////
  /* Payload Structure:
   *
   * <StartCharacter>  ID-CODE  <SeparationCharacter>  REQUEST  <SeparationCharacter>  DATA  <EndCharacter>
   *
   */
  class Payload : public Stewardess::Payload
  {
    // Serializer can see the raw data
    friend class Serializer;

    private:
      // Unique hardware ID of the device
      Stewardess::UniqueID _identifier;
      
      // Request type name
      ProtocolCommand _command;

      // Request body 1
      std::string _data1;

      // Request body 2
      std::string _data2;


    public:
      Payload();

      Payload( Stewardess::UniqueID, ProtocolCommand );

      Payload( Stewardess::UniqueID, ProtocolCommand, std::string, std::string = "" );

      ~Payload();


      Stewardess::UniqueID getID() const { return _identifier; }

      ProtocolCommand getCommand() const { return _command; }

      // Alive command: Component type  --
      const std::string& getDeviceType() const { return _data1; }
      void setDeviceType( std::string s ) { _data1 = s; }
      const std::string& getProperties() const { return _data2; }
      void setProperties( std::string s ) { _data2 = s; }

      // Request/Update command: Variable name  --  Variable value
      const std::string& getVariable() const { return _data1; }
      const std::string& getValue() const { return _data2; }
      void setVariable( std::string  d1 ) { _data1 = d1; }
      void setValue( std::string d2 ) { _data2 = d2; }

      // Event Command
      std::string getEventName() const { return _data1; }
      std::string getEventValue() const { return _data2; }
      void setEventName( std::string n ) { _data1 = n; }
      void setEventValue( std::string v ) { _data2 = v; }

      // Authorize command: Stewardess::UniqueID  --
      Stewardess::UniqueID getStaffID() const;
      void setStaffID( Stewardess::UniqueID );


      std::string print() const;

  };


////////////////////////////////////////////////////////////////////////////////
  /*
   * Sentinel Serializer definition. Inherits from Stewardess::Serialzer
   */
  class Serializer : public Stewardess::Serializer
  {
    private:

    public:
      Serializer();

      ~Serializer();

      // Turns a payload into a character buffer for writing
      virtual void serialize( const Stewardess::Payload* ) override;

      // Turn a character buffer into payload
      virtual void deserialize( const Stewardess::Buffer* ) override;
  };


}

#endif // SENTINEL_PROTOCOL_LIBRARY_H_ 

