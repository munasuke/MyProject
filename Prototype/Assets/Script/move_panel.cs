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
    Vector3[] speed = {
        new Vector3(0, 0, -10),//Down
        new Vector3(0, 0, 10),//Up
        new Vector3(10, 0, 0),//Left
        new Vector3(-10, 0, 0)//Right
    };
	
	public void OnUserAction () {
        for (int i = 0; i < 4; i++) {
            if (CheckMove(vec[i]) == true)
            {
                transform.position += speed[i];
                break;
            }
        }
    }

    //周囲を検索
    bool CheckMove(Vector3 dir) {
        if (Physics.Raycast(transform.position, dir, 10.0f) == true) {
            return false;
        }
        return true;
    }
}
