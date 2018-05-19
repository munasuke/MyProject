using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class move_panel : MonoBehaviour {
    Vector3[] vec = {
        new Vector3(0, 0, -1),//Down
        new Vector3(0, 0, 1),//Up
        new Vector3(1, 0, 0),//Left
        new Vector3(-1, 0, 0)//Right
    };
    Vector3[] move = {
        new Vector3(0, 0, -10),//Down
        new Vector3(0, 0, 10),//Up
        new Vector3(10, 0, 0),//Left
        new Vector3(-10, 0, 0)//Right
    };
    Vector3 target = Vector3.zero;//移動先の保存
    public float speed = 2.0f;
    bool flg = false;

    private void Update() {
        if (flg) {
            for (int i = 0; i < 4; i++) {
                if (CheckMove(vec[i]) == true) {
                    target = transform.position + move[i];
                    transform.position = Vector3.MoveTowards(transform.position, target, speed * Time.deltaTime);
                    break;
                }
            }
            flg = false;
        }
    }

    public void OnUserAction () {
        flg = true;
    }

    int layerMask = 1 << 8;//マスク
    //周囲を検索
    bool CheckMove(Vector3 dir) {
        if (Physics.Raycast(transform.position, dir, 10.0f, layerMask) == true) {
            return false;
        }
        return true;
    }
}
