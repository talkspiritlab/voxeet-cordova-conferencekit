//
//  MediaEngine.h
//  MediaEngine
//
//  Created by Thomas Gourgues on 21/08/12.
//  Copyright (c) 2012-2018 Thomas Gourgues. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "MediaEngineDelegate.h"
#import "WebRTC/RTCVideoRenderer.h"
#import "WebRTC/RTCMediaStream.h"

#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreBluetooth/CBService.h>

typedef enum {
    DeviceiPhone    = 0,
    DeviceSpeaker   = 1,
    DeviceBluetooth = 2,
    DeviceHeadset   = 3,
    DeviceNone      = 4
} AudioDevice;

typedef enum {
    LowProfile  = 0,
    HighProfile = 1
} AudioProfile;

typedef enum {
    kNoQos        = 0,
    kQosConnected = 1,
    kQosLost      = 2
} QosStatus;

RTC_EXPORT
@interface MediaEngine : NSObject {
  
}

@property (nonatomic, assign) id <MediaEngineDelegate> delegate;
- (id)initWithLocalPeer:(NSString *)localPeerId video:(BOOL)video microphone: (BOOL)microphone constraints: (NSDictionary<NSString*, NSString*>*)constraints;
- (void)attachMediaStream:(id<RTCVideoRenderer>)renderer withStream: (RTCMediaStream*) stream;
- (void)unattachMediaStream:(id<RTCVideoRenderer>)renderer withStream: (RTCMediaStream*) stream;
- (RTCMediaStream*)getMediaStream:(NSString*) peerId;
- (RTCMediaStream*)getScreenShareStream;
- (BOOL)needSwitchToPstn;
- (BOOL)createConnectionWithPeer:(NSString *)peerId isMaster:(BOOL)isMaster;
- (BOOL)closeConnectionWithPeer:(NSString *)peerId;
- (BOOL)createAnswerForPeer:(NSString *)peerId;
- (BOOL)setDescriptionForPeer:(NSString *)peerId withSsrc:(long)ssrc type:(NSString *)type andSdp:(NSString *)sdp;
- (BOOL)setCandidateForPeer:(NSString *)peerId withsdpMid:(NSString *)sdpMid sdpIndex:(NSInteger)sdpMLineIndex andSdp:(NSString *)sdp;
- (BOOL)setPositionForPeer:(NSString *)peerId withAngle:(double)angle andPosition:(double)position;
- (BOOL)setPositionForPeer:(NSString *)peerId withAngle:(double)angle position:(double)position andGain:(float)gain;
- (BOOL)setGain:(float)gain forPeer:(NSString *)peerId;
- (void)setMute:(BOOL)mute;
- (void)setPeerMute:(NSString *)peerId mute:(BOOL)mute;
- (void)setAudioOptions:(BOOL)ns agc:(BOOL)agc ec:(BOOL)ec typingDetection:(BOOL)typingDetection;
- (NSString *)getLocalStats:(NSString *)peerId;
- (double)getLocalVuMeter;
- (double)getVuMeterForPeer:(NSString *)peerId;
- (void)enable3DAudio:(BOOL)enable;
- (void)setLoudSpeakerStatus:(BOOL)isEnable;
- (BOOL)isLoudSpeakerActive;
- (void)setHardwareAec:(BOOL)isHardwareAEC;
- (BOOL)isHardwareAec;
- (void)stop;
- (void)dealloc;
- (void)flipCamera;
- (void)startVideo;
- (void)stopVideo;
- (void)startScreenshare:(BOOL)broadcast;
- (void)updateScreenshare:(CMSampleBufferRef)sampleBuffer;
- (void)stopScreenshare;
- (void)resetAudioDevices;

@end
