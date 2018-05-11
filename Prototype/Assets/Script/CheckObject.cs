using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckObject : MonoBehaviour {
    public string plTag = "Player";
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown(0)) {
            Ray ray = new Ray();
            RaycastHit hit = new RaycastHit();
            ray = Camera.main.ScreenPointToRay(Input.mousePosition);

            if (Physics.Raycast(ray.origin, ray.direction, out hit, Mathf.Infinity)) {
                if (hit.collider.gameObject.CompareTag(plTag)) {
                    hit.collider.gameObject.GetComponent<move_sphere>().OnUserAction();
                    Debug.Log(plTag+"よ");
                }
                else {
                    Debug.Log(plTag+"じゃないよ");
                }
            }
        }
	}
}
