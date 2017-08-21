//
//  ViewController.swift
//  MaraTrackDemo-swift
//
//  Created by pk on 2017/8/14.
//  Copyright © 2017年 pk. All rights reserved.
//

import UIKit
import MaraTrackSDK

let kAppKey = "0YZUdPpywBZCQox78ybkQPjJzPqibaN8UT6lj9TjtCbuIrE6LupbJhWbeLoONFml"

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationController?.setNavigationBarHidden(true, animated: false)

        self.checkTrackStatus()
    }

    private func checkTrackStatus() {
        MaraTrackSDK.shared().registerApp(kAppKey) { result in
            if result == .onlineSuccess {
                let config = MaraTrackerConfig()
                let manager = MaraTrackManager(config, delegate: nil)
                let status = manager.getRunStatus()
                if status != .error && status != .notRun {
                    let sb = UIStoryboard(name: "Main", bundle: nil)
                    let runVC = sb.instantiateViewController(withIdentifier: "RunVC")
                    self.navigationController?.pushViewController(runVC, animated: true)
                }
            }
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()

    }
}

