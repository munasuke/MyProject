using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour {
    public float speed = 1.0f;
    Vector3[] dir = {
        (new Vector3(-1.0f, 0.0f, 0.0f)),//Left
        (new Vector3(1.0f,  0.0f, 0.0f)),//Right
        (new Vector3(0.0f,  1.0f, 0.0f)),//Up
        (new Vector3(0.0f, -1.0f, 0.0f))//Down
    };
    KeyCode[] _key = {
        KeyCode.Keypad4,
        KeyCode.Keypad6,
        KeyCode.Keypad8,
        KeyCode.Keypad2
    };

    void Update() {
        if (Input.GetKeyDown(_key[0])) {
            if (CheckBlock(dir[0]) == true) {
                Debug.Log("0");
            }
        }
        if (Input.GetKeyDown(_key[1])) {
            if (CheckBlock(dir[1]) == true) {
                Debug.Log("1");
            }
        }
        if (Input.GetKeyDown(_key[2])) {
            if (CheckBlock(dir[2]) == true) {
                Debug.Log("2");
            }
        }
        if (Input.GetKeyDown(_key[3])) {
            if (CheckBlock(dir[3]) == true) {
                Debug.Log("3");
            }
        }
    }

    //進みたい方向にBlockがあるかチェック
    bool CheckBlock(Vector3 vec) {
        if (Physics.Raycast(transform.position, vec, 1.0f)) {
            return false;
        }
        return true;
    }
}
