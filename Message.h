#ifndef MESSAGE_H__
#define MESSAGE_H__

#include <Arduino.h>

#define SORTIC
// global defined message buffer
#ifdef SORTIC
static PackageMessage packageMessageBuffer[STORELENGTH];                                    ///< instance of package message to store messages
static ErrorMessage errorMessageBuffer[STORELENGTH];                                        ///< instance of error message to store messages
static SBAvailableMessage availableMessageBuffer[STORELENGTH][CONSIGNORSIZE];               ///< instance of smart box available message to store messages
static SBPositionMessage positionMessageBuffer[STORELENGTH][CONSIGNORSIZE];                 ///< instance of smart box position message to store messages
static SBStateMessage stateMessageBuffer[STORELENGTH][CONSIGNORSIZE];                       ///< instance of smart box state message to store messages
static SBtoSOHandshakeMessage handshakeMessageSBToSOBuffer[STORELENGTH][CONSIGNORSIZE];     ///< instance of smart box to sortic handshake message to store messages
#endif

#ifdef BOX
static PackageMessage packageMessageBuffer;
static ErrorMessage errorMessageBuffer;
static SVAvailableMessage availableMessageBuffer[3];
static SVPositionMessage svPositionMessageBuffer;
static SVStateMessage svStateMessageBuffer;
static SBtoSOHandshakeMessage handshakeMessageSBToSOBuffer;
static SBToSVHandshakeMessage handshakeMessageSBToSVBuffer;
static SOPositionMessage soPositionMessageBuffer;
static SOStateMessage soStateMessageBuffer;
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
struct defaultMessage
{
    unsigned int id;
    messageType msgType;
    unsigned int msgLength
    Consignor consignor;
    String topic;
};

/**
 * @brief Package message struct holds all package parameter
 * 
 */
struct PackageMessage
{
    defaultMessage msgFrame = {0, Package, 0};
    String packageId = "-1";
    String cargo = "-1";
    String targetDest = "-1";
    String targetReg = "-1";
};

/**
 * @brief Error message struct holds all error parameter
 * 
 */
struct ErrorMessage
{
    defaultMessage msgFrame = {0, Error, 0};
    bool error;
    bool token;
};

/**
 * @brief Smartbox available message struct holds all available parameter
 * 
 */
struct SBAvailableMessage
{
    defaultMessage msgFrame = {0, SBAvailable, 0};
    String sector = "-1";
    int line = "-1";
    String targetReg = "-1";
};

/**
 * @brief Smartbox position message struct holds all position parameter
 * 
 */
struct SBPositionMessage
{
    defaultMessage msgFrame = {0, SBPosition, 0};
    String sector = "-1";
    int line = "-1";
};

/**
 * @brief Smartbox state message struct holds state
 * 
 */
struct SBStateMessage
{
    defaultMessage msgFrame = {0, SBState, 0};
    String state = "-1";
};

/**
 * @brief Smartbox to Smartvehicle handshake message struct holds all handshake parameter
 * 
 */
struct SBToSVHandshakeMessage
{
    defaultMessage msgFrame = {0, SBToSVHandshake, 0};
    String reck = "-1";
    String ack = "-1";
    String cargo = "-1";
    int line = "-1";
};

/**
 * @brief Smartvehicle available message struct holds all available parameter of Smartvehicle
 * 
 */
struct SVAvailableMessage
{
    defaultMessage msgFrame = {0, SBAvailable, 0};
    String sector = "-1";
    int line = "-1";
};

/**
 * @brief Smartvehicle position message struct holds all position parameter of Smartvehicle
 * 
 */
struct SVPositionMessage
{
    defaultMessage msgFrame = {0, SVPosition, 0};
    String sector = "-1";
    int line = "-1";
};

/**
 * @brief Smartvehicle state message struct holds state of Smartvehicle
 * 
 */
struct SVStateMessage
{
    defaultMessage msgFrame = {0, SVState, 0};
    String state = "-1"; 
};

/**
 * @brief Smartbox to Sortic handshake message struct holds all handshake parameter
 * 
 */
struct SBtoSOHandshakeMessage
{
    defaultMessage msgFrame = {0, SBToSOHandshake, 0};
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
struct SOPositionMessage
{
    defaultMessage msgFrame = {0, SOPosition, 0};
    int line;  
};

/**
 * @brief Sortic state message struct holds state of Sortic
 * 
 */
struct SOStateMessage
{
    defaultMessage msgFrame = {0, SOState, 0};
    String state;
};

#endif