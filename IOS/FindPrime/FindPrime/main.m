//
//  main.m
//  FindPrime
//
//  Created by sijiewang on 10/12/14.
//  Copyright (c) 2014 lnmcc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>


#define MAXPRIME 50

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        int i, p, prevPrime;
        BOOL isPrime;
        NSMutableArray *primes = [NSMutableArray arrayWithCapacity:20];
        [primes addObject: [NSNumber numberWithInteger:2]];
        [primes addObject: [NSNumber numberWithInteger: 3]];
        for(p = 5; p <= MAXPRIME; p += 2) {
            isPrime = YES;
            i = 1;
            do {
                prevPrime = [[primes objectAtIndex: i] integerValue];
                if(p % prevPrime == 0)
                    isPrime = NO;
                ++i;
            } while (isPrime == YES && p / prevPrime >= prevPrime);
                
            if(isPrime)
                [primes addObject: [NSNumber numberWithInteger:p]];
        }
        for(i = 0; i < [primes count]; ++i) {
            NSLog(@"%li", (long)[[primes objectAtIndex: i] integerValue]);
        }
    }
    return 0;
}
