using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class tip_Manager2 : MonoBehaviour
{
    public bool fuseFlag2;
    // Use this for initialization
    void Start()
    {
        fuseFlag2 = false;
    }

    private void OnCollisionEnter(Collision Tip)
    {
        if (Tip.gameObject.CompareTag("fire"))
        {
            fuseFlag2 = true;
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
