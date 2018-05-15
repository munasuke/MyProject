using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//キー入力を受け付ける
public class PlayerKey : MonoBehaviour {

	void Start () {
		
	}
	
	void Update () {
        if (Input.GetKeyDown(KeyCode.Keypad4)) {
            Debug.Log("左よ");
        }
        if (Input.GetKeyDown(KeyCode.Keypad6)) {
            Debug.Log("右よ");
        }
        if (Input.GetKeyDown(KeyCode.Keypad8)) {
            Debug.Log("上よ");
        }
        if (Input.GetKeyDown(KeyCode.Keypad2)) {
            Debug.Log("下よ");
        }
    }
}
