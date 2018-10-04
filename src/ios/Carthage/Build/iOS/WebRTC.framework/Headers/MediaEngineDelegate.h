//
//  VoxeetMediaDelegate.h
//  VoxeetMedia
//
//  Created by Thomas Gourgues on 13/12/12.
//  Copyright (c) 2012 Voxeet. All rights reserved.
//

#import <WebRTC/RTCMacros.h>
#import <Foundation/Foundation.h>

@class RTCMediaStream;

RTC_EXPORT
@protocol MediaEngineDelegate <NSObject>

- (void)audioRouteChanged:(NSNumber *)route;

// New audio core delegate

- (void)sessionCreatedForPeer:(NSString *)peerId withType:(NSString *)type andSdp:(NSString *)sdp;
- (void)iceGatheringCompletedForPeer:(NSString *)peerId withCandidates:(NSArray<NSDictionary<NSString*, id>*> *)candidates;
- (void)printTraceWithLevel:(int)level withMessage:(const char*)message ofLength:(int)length;
- (void)callBackOnChannel:(int)channel withErrorCode:(int)errCode;
- (void)streamAddedForPeer:(NSString*)peerId withStream:(RTCMediaStream*)mediaStream;
- (void)streamUpdatedForPeer:(NSString*)peerId withStream:(RTCMediaStream*)mediaStream;
- (void)streamRemovedForPeer:(NSString*)peerId withStream:(RTCMediaStream*)mediaStream;
- (void)screenStreamAddedForPeer:(NSString*)peerId withStream:(RTCMediaStream*)mediaStream;
- (void)screenStreamRemovedForPeer:(NSString*)peerId withStream:(RTCMediaStream*)mediaStream;

@end
