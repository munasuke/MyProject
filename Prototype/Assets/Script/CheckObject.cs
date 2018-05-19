using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckObject : MonoBehaviour {
    public string panelTag = "Panel";
	
	void Update () {
		if (Input.GetMouseButtonDown(0)) {
            Ray ray = new Ray();
            RaycastHit hit = new RaycastHit();
            ray = Camera.main.ScreenPointToRay(Input.mousePosition);

            //Playerにhitしたか判定
            if (Physics.Raycast(ray.origin, ray.direction, out hit, Mathf.Infinity)) {
                if (hit.collider.gameObject.CompareTag(panelTag)) {
                    hit.collider.gameObject.GetComponent<move_panel>().OnUserAction();
                }
            }
        }
	}
}
