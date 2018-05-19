using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class tip_Manager : MonoBehaviour {

    public bool fuseFlag;
	// Use this for initialization
	void Start ()
    {
        fuseFlag = false;
	}

    private void OnCollisionEnter(Collision Tip)
    {
        if (Tip.gameObject.CompareTag("fire"))
        {
            fuseFlag = true;
        }
    }

    // Update is called once per frame
    void Update () {
        
	}
}

