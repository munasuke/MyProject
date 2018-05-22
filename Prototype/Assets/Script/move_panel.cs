using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class move_panel : MonoBehaviour {

    public void OnUserAction (string tag) {
        Vector3[] vec = {
            Vector3.back,//Down
            Vector3.forward,//Up
            Vector3.right,//Left
            Vector3.left//Right
        };
        Vector3 rota = new Vector3(0.0f, 90.0f, 0.0f);

        for (int i = 0; i < 4; i++) {
            if (CheckMove(vec[i], tag) == true) {
                if (tag == "Panel" || tag == "Panel_union") {
                    transform.position += vec[i]*10;
                }
                if (tag == "Panel_rota") {
                    transform.Rotate(rota);
                }
                Debug.Log(tag);
                break;
            }
        }
    }

    //周囲を検索
    bool CheckMove(Vector3 dir, string tag) {
        int layerMask = 1 << 8;//マスク

        if (tag == "Panel_rota") {
            return true;
        }
        if (tag != "Panel_union") {
            if (Physics.Raycast(transform.position, dir, 10.0f, layerMask) == true) {
                return false;
            }
        }
        else {
            if (transform.localScale.x == 2) {//横長
                if (Physics.Raycast(transform.position + new Vector3(5.0f, 0.0f, 0.0f), dir, 10.0f, layerMask) == true) {
                    return false;
                }
                if (Physics.Raycast(transform.position + new Vector3(-5.0f, 0.0f, 0.0f), dir, 10.0f, layerMask) == true) {
                    return false;
                }
            }
            else if (transform.localScale.z == 2) {//縦長
                if (Physics.Raycast(transform.position + new Vector3(0.0f, 0.0f, 5.0f), dir, 10.0f, layerMask) == true) {
                    return false;
                }
                if (Physics.Raycast(transform.position + new Vector3(0.0f, 0.0f, -5.0f), dir, 10.0f, layerMask) == true) {
                    return false;
                }
            }
        }
        return true;
    }
}
