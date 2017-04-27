//
//  NSObject+DSKeyValueObserverNotification.h
//  DIS_KVC_KVO
//
//  Created by renjinkui on 2017/2/20.
//  Copyright © 2017年 JK. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DSKeyValueChangeDictionary.h"
#import "DSKeyValueProperty.h"


@class DSKeyValueObservationInfo;
@class DSKeyValueObservance;

typedef struct {
    uint16_t retainCount:16;
    uint16_t unknow2:16;
    id object;//4
    id keyOrKeys;//8
    DSKeyValueObservationInfo *observationInfo;//c
    DSKeyValueObservance *observance;//10
    DSKeyValueChange kind;//14
    id oldValue;//18
    id newValue;//1c
    NSIndexSet *indexes;//20
    NSMutableData * extraData;//24
    id forwardingValues_p1;//28
    id forwardingValues_p2;//2c
}DSKVOPendingChangeNotification;

typedef union {
    struct {
        DSKeyValueChange changeKind;
        NSIndexSet *indexes;
    };
    struct {
        DSKeyValueSetMutationKind mutationKind;
        NSSet *objects;
    };
}DSKVOArrayOrSetWillChangeInfo;

typedef struct {
    CFMutableArrayRef pendingArray;//0
    NSUInteger count;//4
    DSKeyValueObservationInfo *observationInfo;//8
    NSUInteger index;//c
    DSKeyValueObservance *observance;//10
}DSKVOPendingInfoPerThreadPush;

typedef struct {
    CFMutableArrayRef pendingArray;//0
    NSUInteger pendingCount;//4
    DSKVOPendingChangeNotification * lastPopedNotification;//8
    NSUInteger lastPopdIndex;//c
    DSKeyValueObservance * observance;//10
}DSKVOPendingInfoPerThreadPop;

typedef struct {
    DSKeyValueObservance *observance;//0
    DSKeyValueChange kind;//4
    id oldValue;//8
    id newValue;//c
    NSIndexSet *indexes;//10
    NSMutableData * extraData;//14
    id forwardingValues_p1;//18
    id forwardingValues_p2;//1c
    BOOL p5;//20
    NSString *keyOrKeys;//24
}DSKVOPendingInfoLocalDetail;

typedef struct {
    NSUInteger capacity;//0
    BOOL isStackBuff;//4
    DSKVOPendingInfoLocalDetail *detailsBuff;//8
    NSUInteger detailsCount;//c
    BOOL p5;//10
    id p6;//14
}DSKVOPendingInfoLocalPush;

typedef struct {
    DSKVOPendingInfoLocalDetail *detailsBuff;//0
    NSUInteger detailsCount;//4
    id observer;//8
    id oldValue;//c
    id forwardValues_p1;//10
    DSKeyValueObservationInfo *observationInfo;//14
}DSKVOPendingInfoLocalPop;

typedef void (*DSKeyValueWillChangeByCallback)(DSKeyValueChangeDetails *, id , NSString *, BOOL , int , NSDictionary *, BOOL *);
typedef void (*DSKeyValuePushPendingNotificationCallback)(id , id , DSKeyValueObservance *, DSKeyValueChangeDetails  , DSKeyValuePropertyForwardingValues , void *);

typedef void (*DSKeyValueDidChangeByCallback)(DSKeyValueChangeDetails *, id , NSString *, BOOL , int , DSKeyValueChangeDetails );
typedef BOOL (*DSKeyValuePopPendingNotificationCallback)(id ,id , DSKeyValueObservance **, DSKeyValueChangeDetails *,DSKeyValuePropertyForwardingValues *,id *, void * );

void DSKeyValueWillChange(id object, id keyOrKeys, BOOL isASet, DSKeyValueObservationInfo *observationInfo, DSKeyValueWillChangeByCallback willChangeByCallback, void *changeInfo, DSKeyValuePushPendingNotificationCallback pushPendingNotificationCallback, void *pendingInfo, DSKeyValueObservance *observance) ;
void DSKeyValueDidChange(id object, id keyOrKeys, BOOL isASet,DSKeyValueDidChangeByCallback didChangeByCallback, DSKeyValuePopPendingNotificationCallback popPendingNotificationCallback, void *pendingInfo);

void DSKeyValueNotifyObserver(id observer,NSString * keyPath, id object, void *context, id originalObservable, BOOL isPriorNotification, DSKeyValueChangeDetails changeDetails, DSKeyValueChangeDictionary **pChange);

void DSKeyValueDidChangeBySetting(DSKeyValueChangeDetails *resultChangeDetails, id object, NSString *keyPath, BOOL equal, int options, DSKeyValueChangeDetails changeDetails) ;
BOOL DSKeyValuePopPendingNotificationLocal(id object,id keyOrKeys, DSKeyValueObservance **observance, DSKeyValueChangeDetails *changeDetails,DSKeyValuePropertyForwardingValues *forwardValues,id *findKeyOrKeys, DSKVOPendingInfoLocalPop* pendingInfo);
BOOL DSKeyValuePopPendingNotificationPerThread(id object,id keyOrKeys, DSKeyValueObservance **observance, DSKeyValueChangeDetails *changeDetails,DSKeyValuePropertyForwardingValues *forwardValues,id *findKeyOrKeys, DSKVOPendingInfoPerThreadPop* pendingInfo);

void DSKeyValueWillChangeBySetting(DSKeyValueChangeDetails *changeDetails, id object, NSString *affectedKeyPath, BOOL match, int options, NSDictionary *oldValueDict, BOOL *detailsRetained);
void DSKeyValuePushPendingNotificationLocal(id object, id keyOrKeys, DSKeyValueObservance *observance, DSKeyValueChangeDetails changeDetails , DSKeyValuePropertyForwardingValues forwardingValues, DSKVOPendingInfoLocalPush *pendingInfo);
void DSKeyValuePushPendingNotificationPerThread(id object, id keyOrKeys, DSKeyValueObservance *observance, DSKeyValueChangeDetails changeDetails , DSKeyValuePropertyForwardingValues forwardingValues, DSKVOPendingInfoPerThreadPush *pendingInfo) ;

@interface NSObject (DSKeyValueObserverNotification)

@end

