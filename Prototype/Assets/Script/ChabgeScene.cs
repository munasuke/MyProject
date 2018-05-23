using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ChabgeScene : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButton(1)) {
            if (SceneManager.GetActiveScene().name == "main") {
                SceneManager.LoadScene("End");
            }
            else {
                SceneManager.LoadScene("main");
            }
        }
	}
}
