using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ChabgeScene : MonoBehaviour {
    /*
     * Title <---> StageSelect//botton
     * StageSelect ----> Game//botton
     * Game ----> Result//flg
     * Game <---> Pause//botton
     * Result ----> StageSelect//botton
     * Pause ----> StageSelect//botton
     */
	void Update () {
        bool sflag = false;
		if (Input.GetMouseButton(1)) {
            sflag = true;
        }
        SceneUpdate(sflag);
	}

    void SceneUpdate(bool flg) {
        if (flg) {
            switch (SceneManager.GetActiveScene().name) {
                case "main":
                    SceneManager.LoadScene("End");
                    break;
                case "End":
                    SceneManager.LoadScene("main");
                    break;
                default:
                    break;
            }
            flg = false;
        }
    }
}
