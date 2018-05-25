using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class test : MonoBehaviour {
    Vector3 rota = new Vector3(0, 90, 0);
    public float sp = 2.0f;
    Vector3 pos;
	// Use this for initialization
	void Start () {
        pos = transform.position;
    }

    // Update is called once per frame
    void Update () {
		if (Input.GetMouseButtonDown(2)) {
            transform.Rotate(rota);
        }
        if (Input.GetKeyDown(KeyCode.A)) {
            pos.x += Mathf.Cos(transform.rotation.y * Mathf.Deg2Rad);
            pos.z -= Mathf.Sin(transform.rotation.y * Mathf.Deg2Rad);
            transform.position = pos;
        }
	}
}
