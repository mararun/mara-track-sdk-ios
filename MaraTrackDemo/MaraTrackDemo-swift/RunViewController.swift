//
//  RunViewController.swift
//  MaraTrackDemo
//
//  Created by pk on 2017/8/15.
//  Copyright © 2017年 com.maramara. All rights reserved.
//

import UIKit
import MaraTrackSDK

class RunViewController: UIViewController {

    @IBOutlet weak var distLabel: UILabel!
    @IBOutlet weak var avrPaceLabel: UILabel!
    @IBOutlet weak var curPaceLabel: UILabel!
    @IBOutlet weak var timeLabel: UILabel!
    @IBOutlet weak var startPauseBtn: UIButton!
    @IBOutlet weak var statusLabel: UILabel!

    fileprivate var trackManager: MaraTrackManager?
    var locationManager: MaraLocationManager?
    
    fileprivate var tipsTask: TrackTask? {
        didSet {
            if let task = tipsTask {
                self.distLabel.text = String(format: "%0.2f", floor(task.distance/10)/100)
                self.timeLabel.text = Double(task.time).ext_hhmmssClockStringLimit()
                self.avrPaceLabel.text = task.avrPace.ext_mmssPaceString()
                self.curPaceLabel.text = task.curPace.ext_mmssPaceString()
            }
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        let config = MaraTrackerConfig()
        config.enableHA = true
        config.enableAutoPause = true
        self.trackManager = MaraTrackManager(config, locManager: self.locationManager, delegate: self)
        self.trackManager?.startRun()
    }

    @IBAction func startOrPauseDidClicked(_ sender: UIButton) {
        /// true 继续, false 暂停
        if sender.isSelected == true {
            self.trackManager?.resumeRun()
//            self.statusLabel.text = "跑步中";
        } else {
            self.trackManager?.pauseRun()
//            self.statusLabel.text = "手动暂停";
        }
        sender.isSelected = !sender.isSelected
    }

    @IBAction func stopDidClicked(_ sender: UIButton) {
        self.trackManager?.stopRun()
        if let trackInfo = self.trackManager?.getRunDetailJson() {
            debugPrint("trackinfo = \(trackInfo)")
        }
        self.navigationController?.popViewController(animated: true)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()

    }

}

extension RunViewController: MaraTrackManagerDelegate {

    func maraTrackManager(_ manager: MaraTrackManager, didUpdateData task: TrackTask) {
        self.tipsTask = task
    }

    func maraTrackManager(_ manager: MaraTrackManager, didUpdate status: TrackerStatus) {
        if (status == .autoPaused) {
            self.statusLabel.text = "自动暂停";
            debugPrint("自动暂停")
        } else if (status == .paused) {
            self.statusLabel.text = "手动暂停";
        } else if (status == .run) {
            self.statusLabel.text = "跑步中";
        }
    }

    func maraTrackManager(_ manager: MaraTrackManager, didUpdate location: MaraUserLocation) {

    }

    func maraTrackManager(_ manager: MaraTrackManager, restoreInterruptData json: String) {
        self.startPauseBtn.isSelected = true
        self.statusLabel.text = "恢复跑步,点击继续";
    }
}
