using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour {
    public float speed = 2.0f;
    Vector3 target;

    private void Start() {
        target = transform.position;
    }

    void Update() {
        if (target == transform.position) {
            SetTargetPos();
        }
        transform.position = Vector3.MoveTowards(transform.position, target, speed * Time.deltaTime);
        //if (Input.GetKeyDown(KeyCode.Keypad8)) {
        //}
        //if (Input.GetKeyDown(KeyCode.Keypad2)) {
        //}
    }

    void SetTargetPos() {
        Vector3[] dir = {
            Vector3.left,//Left
            Vector3.right,//Right
            Vector3.up,//Up
            Vector3.down//Down
        };

        if (Input.GetKeyDown(KeyCode.Keypad4)) {
            if (CheckBlock(dir[0])) {
                target = transform.position + dir[0];
                return;
            }
        }
        if (Input.GetKeyDown(KeyCode.Keypad6)) {
            if (CheckBlock(dir[1])) {
                target = transform.position + dir[1];
                return;
            }
        }
    }

    //進みたい方向に障害物があるかチェック
    bool CheckBlock(Vector3 vec) {
        int layerMask = 1 << 8;
        if (Physics.Raycast(transform.position, vec, 1.0f, layerMask)) {
            return false;
        }
        return true;
    }
}
