#ifndef MESSAGE_H__
#define MESSAGE_H__

#include <Arduino.h>

#define SORTIC
// global defined message buffer
static ErrorMessage errorMessageBuffer[STORELENGTH];                                        ///< instance of error message to store messages
static PackageMessage packageMessageBuffer[STORELENGTH][PACKAGESTORAGE];                    ///< instance of package message to store messages  

#ifdef SORTIC                    
static SBAvailableMessage sbAvailableMessageBuffer[STORELENGTH][CONSIGNORSIZE];               ///< instance of smart box available message to store messages
static SBPositionMessage sbPositionMessageBuffer[STORELENGTH][CONSIGNORSIZE];                 ///< instance of smart box position message to store messages
static SBStateMessage sbStateMessageBuffer[STORELENGTH][CONSIGNORSIZE];                       ///< instance of smart box state message to store messages
static SBtoSOHandshakeMessage handshakeMessageSBToSOBuffer[STORELENGTH];                      ///< instance of smart box to sortic handshake message to store messages
#endif

#ifdef BOX
static SVAvailableMessage svAvailableMessageBuffer[STORELENGTH][CONSIGNORSIZE];
static SVPositionMessage svPositionMessageBuffer[STORELENGTH][CONSIGNORSIZE];
static SVStateMessage svStateMessageBuffer[STORELENGTH][CONSIGNORSIZE];
static SBtoSOHandshakeMessage handshakeMessageSBToSOBuffer[STORELENGTH];
static SBToSVHandshakeMessage handshakeMessageSBToSVBuffer[STORELENGTH][CONSIGNORSIZE];
static SOPositionMessage soPositionMessageBuffer[STORELENGTH];
static SOStateMessage soStateMessageBuffer[STORELENGTH];
#endif

#ifdef VEHICLE
// define messagebuffers for vehicle
#endif

/**
 * @brief Message type class holds all possible message types
 * 
 */
enum class MessageType
{
    Package
    Error
    SBAvailable
    SBPosition
    SBState
    SBToSVHandshake
    SVAvailable
    SVPosition
    SVState
    SBToSOHandshake
    SOPosition
    SOState
};

/**
 * @brief Consignor class holds all possible consignors
 * 
 */
enum class Consignor
{
    DEFUALTCONSIGNOR
    SO1
    SB1
    SB2
    SB3
    SV1
    SV2
    SV3
};

/**
 * @brief Default message struct for default message frame
 * 
 */
struct MessageFrame
{
    unsigned int msgId = 0;
    messageType msgType;
    unsigned int msgLength = 0;
    Consignor msgConsignor = MessageTpye::DEFUALTCONSIGNOR;
};

/**
 * @brief Package message struct holds all package parameter
 * 
 */
struct PackageMessage : MessageFrame
{
    msgType = MessageType::Package;
    unsigned int packageId = 0;
    String cargo = "-1";
    String targetDest = "-1";
    String targetReg = "-1";
};

/**
 * @brief Error message struct holds all error parameter
 * 
 */
struct ErrorMessage : MessageFrame
{
    msgType = MessageType::Error;
    bool error;
    bool token;
};

/**
 * @brief Smartbox available message struct holds all available parameter
 * 
 */
struct SBAvailableMessage : MessageFrame
{
    msgType = MessageType::SBAvailable;
    String sector = "-1";
    int line = "-1";
    String targetReg = "-1";
};

/**
 * @brief Smartbox position message struct holds all position parameter
 * 
 */
struct SBPositionMessage : MessageFrame
{
    msgType = MessageType::SBPosition;
    String sector = "-1";
    int line = "-1";
};

/**
 * @brief Smartbox state message struct holds state
 * 
 */
struct SBStateMessage : MessageFrame
{
    msgType = MessageType::SBState;
    String state = "-1";
};

/**
 * @brief Smartbox to Smartvehicle handshake message struct holds all handshake parameter
 * 
 */
struct SBToSVHandshakeMessage : MessageFrame
{
    msgType = MessageType::SBToSVHandshake;
    String reck = "-1";
    String ack = "-1";
    String cargo = "-1";
    int line = "-1";
};

/**
 * @brief Smartvehicle available message struct holds all available parameter of Smartvehicle
 * 
 */
struct SVAvailableMessage : MessageFrame
{
    msgType = MessageType::SVAvailable;
    String sector = "-1";
    int line = "-1";
};

/**
 * @brief Smartvehicle position message struct holds all position parameter of Smartvehicle
 * 
 */
struct SVPositionMessage : MessageFrame
{
    msgType = MessageType::SVPosition;
    String sector = "-1";
    int line = "-1";
};

/**
 * @brief Smartvehicle state message struct holds state of Smartvehicle
 * 
 */
struct SVStateMessage : MessageFrame
{
    msgType = MessageType::SVState;
    String state = "-1"; 
};

/**
 * @brief Smartbox to Sortic handshake message struct holds all handshake parameter
 * 
 */
struct SBToSOHandshakeMessage : MessageFrame
{
    msgType = MessageType::SBToSOHandshake;
    String reck = "-1";
    String ack = "-1";
    String cargo = "-1";
    String targetReg = "-1";
    int line = "-1";
};

/**
 * @brief Sortic position message struct holds position of Sortic
 * 
 */
struct SOPositionMessage : MessageFrame
{
    msgType = MessageType::SOPosition;
    int line;  
};

/**
 * @brief Sortic state message struct holds state of Sortic
 * 
 */
struct SOStateMessage : MessageFrame
{
    msgType = MessageType::SOState;
    String state;
};

#endif