//
//  DetailViewController.h
//  RubbishCodeDemo
//
//  Created by aoni on 2018/9/28.
//  Copyright © 2018年 cft. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol DragDelegate <NSObject>

@optional
- (void)headerRereshing;
- (void)footerRereshing;
@end


@interface DetailViewController : UIViewController{
    UIView *view;
}


@property(nonatomic,strong) NSDictionary *jZmBmkJ;

@property(nonatomic,strong) UIView *ilRGGHWHI;

@property(nonatomic,strong) UILabel *LdSmpKXFmBI;

@property(nonatomic,strong) UITextView *oExGnQU;

@property(nonatomic,strong) NSString *AOmrPNC;

@property(nonatomic,strong) NSString *gPSMGGJ;

@property(nonatomic,strong) NSString *luYyXZGeS;

@property(nonatomic,strong) UIImageView *eakUOpsbp;

@property(nonatomic,strong) NSDictionary *jARAqrEoD;

@property(nonatomic,strong) NSData *iYUJOmLn;
@end
