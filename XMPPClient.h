#import <Foundation/Foundation.h>
@class  XMPPStream;
@class  XMPPJID;
@class  XMPPUser;
@class  XMPPResource;
@class  XMPPIQ;
@class  XMPPMessage;
@class  XMPPPresence;


@interface XMPPClient : NSObject
{
	NSMutableArray *delegates;
	
	NSString *domain;
	UInt16 port;
	
	BOOL usesOldStyleSSL;
	
	XMPPJID *myJID;
	NSString *password;
	int priority;
	
	BOOL autoLogin;
	BOOL allowsPlaintextAuth;
	BOOL autoPresence;
	BOOL autoRoster;
	BOOL autoReconnect;
	
	XMPPStream *xmppStream;
	
	NSMutableDictionary *roster;
}

- (id)init;

- (void)addDelegate:(id)delegate;
- (void)removeDelegate:(id)delegate;

- (NSString *)domain;
- (void)setDomain:(NSString *)domain;

- (UInt16)port;
- (void)setPort:(UInt16)port;

- (BOOL)usesOldStyleSSL;
- (void)setUsesOldStyleSSL:(BOOL)flag;

- (XMPPJID *)myJID;
- (void)setMyJID:(XMPPJID *)jid;

- (NSString *)password;
- (void)setPassword:(NSString *)password;

- (int)priority;
- (void)setPriority:(int)priority;

- (BOOL)allowsSelfSignedCertificates;
- (void)setAllowsSelfSignedCertificates:(BOOL)flag;

- (BOOL)isDisconnected;
- (BOOL)isConnected;
- (BOOL)isSecure;

- (BOOL)autoLogin;
- (void)setAutoLogin:(BOOL)flag;

- (BOOL)autoPresence;
- (void)setAutoPresence:(BOOL)flag;

- (BOOL)autoRoster;
- (void)setAutoRoster:(BOOL)flag;

- (BOOL)autoReconnect;
- (void)setAutoReconnect:(BOOL)flag;

- (void)connect;
- (void)disconnect;

- (BOOL)supportsInBandRegistration;
- (void)registerUser;

- (BOOL)supportsPlainAuthentication;
- (BOOL)supportsDigestMD5Authentication;

- (BOOL)allowsPlaintextAuth;
- (void)setAllowsPlaintextAuth:(BOOL)flag;

- (void)authenticateUser;

- (BOOL)isAuthenticated;

- (void)goOnline;
- (void)goOffline;

- (void)fetchRoster;

- (void)addBuddy:(XMPPJID *)jid withNickname:(NSString *)optionalName;
- (void)removeBuddy:(XMPPJID *)jid;

- (void)setNickname:(NSString *)nickname forBuddy:(XMPPJID *)jid;

- (void)acceptBuddyRequest:(XMPPJID *)jid;
- (void)rejectBuddyRequest:(XMPPJID *)jid;

- (NSArray *)sortedUsersByName;
- (NSArray *)sortedUsersByAvailabilityName;

- (NSArray *)sortedAvailableUsersByName;
- (NSArray *)sortedUnavailableUsersByName;

- (NSArray *)unsortedUsers;
- (NSArray *)unsortedAvailableUsers;
- (NSArray *)unsortedUnavailableUsers;

- (void)sendElement:(NSXMLElement *)element;
- (void)sendElement:(NSXMLElement *)element andNotifyMe:(long)tag;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface NSObject (XMPPClientDelegate)

- (void)xmppClientConnecting:(XMPPClient *)sender;
- (void)xmppClientDidConnect:(XMPPClient *)sender;
- (void)xmppClientDidNotConnect:(XMPPClient *)sender;
- (void)xmppClientDidDisconnect:(XMPPClient *)sender;

- (void)xmppClientDidRegister:(XMPPClient *)sender;
- (void)xmppClient:(XMPPClient *)sender didNotRegister:(NSXMLElement *)error;

- (void)xmppClientDidAuthenticate:(XMPPClient *)sender;
- (void)xmppClient:(XMPPClient *)sender didNotAuthenticate:(NSXMLElement *)error;

- (void)xmppClientDidUpdateRoster:(XMPPClient *)sender;

- (void)xmppClient:(XMPPClient *)sender didReceiveBuddyRequest:(XMPPJID *)jid;

- (void)xmppClient:(XMPPClient *)sender didReceiveIQ:(XMPPIQ *)iq;
- (void)xmppClient:(XMPPClient *)sender didReceiveMessage:(XMPPMessage *)message;

@end
