using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckObject : MonoBehaviour {
    string[] panelTag = {
        "Panel",//ノーマル
        "Panel_fixed",//固定
        "Panel_union",//合体
        "Panel_rota"//回転
    };
	
	void Update () {
		if (Input.GetMouseButtonDown(0)) {
            Ray ray = new Ray();
            RaycastHit hit = new RaycastHit();
            ray = Camera.main.ScreenPointToRay(Input.mousePosition);

            //Panelにhitしたか判定
            if (Physics.Raycast(ray.origin, ray.direction, out hit, Mathf.Infinity)) {
                for (int i = 0; i < panelTag.Length; i++) {
                    if (hit.collider.gameObject.CompareTag(panelTag[i])) {
                        hit.collider.gameObject.GetComponent<move_panel>().OnUserAction(panelTag[i]);
                    }
                }
            }
        }
	}
}
