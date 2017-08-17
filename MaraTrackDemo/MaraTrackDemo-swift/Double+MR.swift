//
//  Double+MR.swift
//  MaraTrackDemo
//
//  Created by pk on 2017/7/31.
//  Copyright © 2017年 pk. All rights reserved.
//

import Foundation

extension Double {

    // 转化数字为 时、分、秒 形式
    private func private_hhmmssTuple() -> (h: Int, m: Int, s: Int) {
        let value = self > 0 ? self : 0
        let timeLength = value < Double(Int.max) ? Int(value) : Int.max
        let hour = timeLength/3600
        let min = (timeLength%3600)/60
        let second = timeLength%60
        return (hour, min, second)
    }

    // 时间长度转为 12:02:01 格式，最大 99:59:59
    func ext_hhmmssClockStringLimit() -> String {
        var tuple = self.private_hhmmssTuple()
        if tuple.h >= 100 {
            tuple = (99, 59, 59)
        }
        let clockString = String(format: "%02d:%02d:%02d", tuple.h, tuple.m, tuple.s)
        return clockString
    }

    // 转化数字为 配速分、配速秒 形式
    private func private_mmssPaceTuple() -> (pm: Int, ps: Int) {
        let value = self > 0 ? self : 0
        let timeLength = value < Double(Int.max) ? Int(value) : Int.max
        let min = timeLength/60
        let second = timeLength%60
        return (min, second)
    }

    // 时间长度转为 19’50” 配速格式，最大 59’59”
    func ext_mmssPaceString() -> String {
        var tuple = self.private_mmssPaceTuple()
        if tuple.pm >= 60 {
            tuple = (59, 59)
        }
        let paceString = String(format: "%02d'%02d\"", tuple.pm, tuple.ps)
        return paceString
    }
}
