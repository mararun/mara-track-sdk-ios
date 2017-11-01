//
//  ViewController.swift
//  MaraTrackDemo-swift
//
//  Created by pk on 2017/8/14.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

import UIKit
import MaraTrackSDK

class ViewController: UIViewController {

    let locationManager = MaraLocationManager()
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationController?.setNavigationBarHidden(true, animated: false)

        self.locationManager.startUpdatingLocation()
        
        self.checkTrackStatus()
    }

    private func checkTrackStatus() {
        let config = MaraTrackerConfig()
        let manager = MaraTrackManager(config, locManager: nil, delegate: nil)
        let status = manager.getRunStatus()
        if status != .error && status != .notRun {
            let sb = UIStoryboard(name: "Main", bundle: nil)
            let runVC = sb.instantiateViewController(withIdentifier: "RunVC") as! RunViewController
            runVC.locationManager = locationManager
            self.navigationController?.pushViewController(runVC, animated: true)
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()

    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        let vc = segue.destination
        if vc.isKind(of: RunViewController.self) {
            (vc as! RunViewController).locationManager = self.locationManager
        }
    }
}

