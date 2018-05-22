﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class move_panel : MonoBehaviour {
    public float speed = 3.0f;
    Vector3 target;
    bool flg = false;

    private void Start() {
        target = transform.position;
    }

    private void Update () {
        string[] panelTag = {
            "Panel",//ノーマル
            "Panel_fixed",//固定
            "Panel_union",//合体
            "Panel_rota"//回転
        };

        if (Input.GetMouseButtonDown(0)) {
            flg = true;
        }
        Ray ray = new Ray();
        RaycastHit hit = new RaycastHit();
        ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        //Panelにhitしたか判定
        if (Physics.Raycast(ray.origin, ray.direction, out hit, Mathf.Infinity)) {
            for (int i = 0; i < panelTag.Length; i++) {
                if (hit.collider.gameObject.CompareTag(panelTag[i])) {
                    while (flg == true) {
                        PanelAction(panelTag[i]);
                        flg = false;
                    }
                }
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

    //パネルの行動
    void PanelAction(string tag) {
        Vector3[] vec = {
            Vector3.back,//Down
            Vector3.forward,//Up
            Vector3.right,//Left
            Vector3.left//Right
        };
        Vector3 rota = new Vector3(0.0f, 90.0f, 0.0f);

        for (int i = 0; i < vec.Length; i++) {
            if (CheckMove(vec[i], tag) == true) {
                if (tag == "Panel" || tag == "Panel_union") {
                    if (target == transform.position) {
                        target = transform.position + vec[i] * 10;
                    }
                    transform.position = Vector3.MoveTowards(transform.position, target, speed * Time.deltaTime);
                    break;
                }
                if (tag == "Panel_rota") {
                    transform.Rotate(rota);
                    break;
                }
                Debug.Log(tag);
                break;
            }
        }
    }
}
