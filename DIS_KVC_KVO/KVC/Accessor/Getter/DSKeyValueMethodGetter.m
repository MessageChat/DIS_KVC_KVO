//
//  DSKeyValueMethodGetter.m
//  DIS_KVC_KVO
//
//  Created by renjinkui on 2017/1/7.
//  Copyright © 2017年 JK. All rights reserved.
//

#import "DSKeyValueMethodGetter.h"
#import "DSGetValueWithMethod.h"

@implementation DSKeyValueMethodGetter
- (id)initWithContainerClassID:(id)containerClassID key:(NSString *)key method:(Method)method {
    NSUInteger argumentsCount = method_getNumberOfArguments(method);
    if(argumentsCount == 2) {
        char *returnType = method_copyReturnType(method);
        IMP imp = NULL;
        NSUInteger augumentCount = 1;
        switch (returnType[0]) {
            case '#':
            case '@': {
                imp = method_getImplementation(method);
                augumentCount = 0;
            } break;
            case 'B': {
                imp = (IMP)_DSGetBoolValueWithMethod;
            } break;
            case 'C': {
                imp = (IMP)_DSGetUnsignedCharValueWithMethod;
            } break;
            case 'I': {
                imp = (IMP)_DSGetUnsignedIntValueWithMethod;
            } break;
            case 'Q': {
                imp = (IMP)_DSGetUnsignedLongLongValueWithMethod;
            } break;
            case 'L': {
                imp = (IMP)_DSGetUnsignedLongValueWithMethod;
            } break;
            case 'S': {
                imp = (IMP)_DSGetUnsignedShortValueWithMethod;
            } break;
            case 'c': {
                imp = (IMP)_DSGetCharValueWithMethod;
            } break;
            case 'd': {
                imp = (IMP)_DSGetDoubleValueWithMethod;
            } break;
            case 'f': {
                imp = (IMP)_DSGetFloatValueWithMethod;
            } break;
            case 'i': {
                imp = (IMP)_DSGetIntValueWithMethod;
            } break;
            case 'l': {
                imp = (IMP)_DSGetLongValueWithMethod;
            } break;
            case 'q': {
                imp = (IMP)_DSGetLongLongValueWithMethod;
            } break;
            case 's': {
                imp = (IMP)_DSGetShortValueWithMethod;
            } break;
            case '{': {
                if (strcmp(returnType, "{CGPoint=ff}") == 0){
                    imp = (IMP)_DSGetPointValueWithMethod;
                }
                else if (strcmp(returnType, "{_NSPoint=ff}") == 0){
                    imp = (IMP)_DSGetPointValueWithMethod;
                }
                else if (strcmp(returnType, "{_NSRange=II}") == 0){
                    imp = (IMP)_DSGetRangeValueWithMethod;
                }
                else if (strcmp(returnType, "{CGRect={CGPoint=ff}{CGSize=ff}}") == 0){
                    imp = (IMP)_DSGetRectValueWithMethod;
                }
                else if (strcmp(returnType, "{_NSRect={_NSPoint=ff}{_NSSize=ff}}") == 0){
                    imp = (IMP)_DSGetRectValueWithMethod;
                }else if (strcmp(returnType, "{CGSize=ff}") == 0){
                    imp = (IMP)_DSGetSizeValueWithMethod;
                }
                else if (strcmp(returnType, "{_NSSize=ff}") == 0){
                    imp = (IMP)_DSGetSizeValueWithMethod;
                }
                else {
                    imp = (IMP)_DSGetValueWithMethod;
                }
            } break;
        }
        
        free(returnType);
        if(imp) {
            void *arguments[3] = {0};
            if(argumentsCount > 0) {
                arguments[0] = method;
            }
            return [super initWithContainerClassID:containerClassID key:key implementation:imp selector:method_getName(method) extraArguments:arguments count:argumentsCount];
        }
        else {
            [self release];
            return nil;
        }
    }
    else {
        [self release];
        return nil;
    }
}
@end