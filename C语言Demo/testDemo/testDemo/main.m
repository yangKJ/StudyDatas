//
//  main.m
//  testDemo
//
//  Created by 杨科军 on 2019/11/8.
//  Copyright © 2019 杨科军. All rights reserved.
//

#import <Foundation/Foundation.h>
void test1(void);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        test1();
    }
    return 0;
}

/// 结构体嵌套
void test1(void){
    // 定义一个时间结构体类型
    // 出生时间
    struct Time {
        int HH;
        int mm;
        int ss;
    };
    
    struct Date {
        int year;
        int month;
        int day;
        struct Time time;
    };

    struct Date date = {1998,3,4,{12,13,14}};
    NSLog(@"year = %i,HH = %i",date.year,date.time.HH);
}

void test2(){

}
