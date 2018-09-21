//
//  MediaAPI.h
//  VoxeetMedia
//
//  Created by Gilles Bordas on 09/01/2014.
//  Copyright (c) 2014 Voxeet. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WebRTC/WebRTC.h>
#import "SdpMessage.h"
#import "SdpCandidates.h"
#import "SdpDescription.h"
#import "SenderNetworkStatistics.h"
#import "ReceiverNetworkStatistics.h"
#import "NetworkCodec.h"

@protocol MediaAPIDelegate <NSObject>
  - (void)sessionCreatedForPeer:(NSString *)peerId withType:(NSString *)type andSdp:(NSString *)sdp;
  - (void)iceGatheringCompletedForPeer:(NSString *)peerId withCandidates:(NSArray<NSDictionary<NSString*, id>*> *)candidates;
  - (void)streamAddedForPeer:(NSString *)peerId withStream:(RTCMediaStream *)mediaStream;
  - (void)streamRemovedForPeer:(NSString *)peerId withStream:(RTCMediaStream *)mediaStream;
  - (void)streamUpdatedForPeer:(NSString *) peerId withStream:(RTCMediaStream *)mediaStream;
  - (void)screenShareStreamAddedForPeer:(NSString *)peerId withStream:(RTCMediaStream *)mediaStream;
  - (void)screenShareStreamRemovedForPeer:(NSString *)peerId withStream:(RTCMediaStream *)mediaStream;
@end

@interface MediaAPI : NSObject <MediaEngineDelegate>

@property (nonatomic, assign) id<MediaAPIDelegate> delegate;
@property (strong, nonatomic) NSMutableDictionary *pendingOperations;
@property (strong, nonatomic) SdpCandidates *peerCandidates;
@property (strong, nonatomic) MediaEngine *wrapper;
@property (copy, nonatomic) void(^audioRouteChangedBlock)(NSNumber *);

- (id)initWithLocalPeer:(NSString *)localPeerId video:(BOOL)video microphone:(BOOL)microphone constraints: (NSDictionary<NSString*, NSString*>*)constraints;
- (void)stop;
- (void)setHardwareAEC:(BOOL)isHardwareAEC;
- (BOOL)isHardwareAEC;
- (void)setLoudSpeakerStatus:(BOOL)isEnable;
- (BOOL)isLoudSpeakerActive;
- (BOOL)needSwitchToPstn;
- (SdpMessage *)createOfferForPeer:(NSString *)peerId isMaster:(BOOL)isMaster;
- (SdpMessage *)createAnswerForPeer:(NSString *)peerId withSSRC:(UInt32)ssrc offer:(SdpDescription *)offer andCandidates:(NSArray *)candidates isMaster:(BOOL)isMaster;
- (void)addPeerFromAnswer:(NSString *)peerId withSSRC:(long)ssrc answer:(SdpDescription *)answer candidates:(NSArray *)candidates;
- (void)removePeer:(NSString *)peerId;
- (void)changePeerPosition:(NSString *)peerId withAngle:(double)angle andDistance:(double)distance;
- (void)changePeerPosition:(NSString *)peerId withAngle:(double)angle distance:(double)distance andGain:(float)gain;
- (void)changeGain:(float)gain forPeer:(NSString *)peerId;
- (void)attachMediaStream:(id<RTCVideoRenderer>)renderer withStream:(RTCMediaStream *)stream;
- (void)unattachMediaStream:(id<RTCVideoRenderer>)renderer withStream:(RTCMediaStream *)stream;
- (RTCMediaStream*)getMediaStream:(NSString *)peerId;
- (RTCMediaStream*)getScreenShareStream;
- (void)setMute:(BOOL)mute;
- (void)setPeerMute:(NSString *)peerId mute:(BOOL)mute;
- (double)getLocalVuMeterLevel;
- (double)getPeerVuMeterLevel:(NSString *)peerId;
- (void)flipCamera;
- (void)startVideo;
- (void)stopVideo;
- (void)resetAudioDevices;
- (void)startScreenShare:(BOOL)broadcast;
- (void)updateScreenshare:(CMSampleBufferRef)sampleBuffer;
- (void)stopScreenShare;
- (void)enable3DAudio:(BOOL)enable;

@end
