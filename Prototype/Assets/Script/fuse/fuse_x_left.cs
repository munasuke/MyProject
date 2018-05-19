using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class fuse_x_left : MonoBehaviour {

    public GameObject fusecheck;
    public GameObject fusecheck2;

    public GameObject Centercheck;

    public GameObject fuse_x_right;
    public GameObject fuse_z_up;
    public GameObject fuse_z_down;

    private bool FuseFlag = false;
    private bool FuseFlag2 = false;
    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        FuseFlag = fusecheck.GetComponent<tip_Manager>().fuseFlag;
        FuseFlag2 = fusecheck2.GetComponent<tip_Manager2>().fuseFlag2;

        //右から当たると右から消えだす
        if (FuseFlag)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position -= new Vector3(Time.deltaTime, 0, 0);
            if (this.transform.localScale.x < 0)
            {
                Destroy(this.gameObject);
            }
        }

        //左から当たると左から消えだす
        if (FuseFlag2)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position += new Vector3(Time.deltaTime, 0, 0);
            if (this.transform.localScale.x < 0)
            {
                Destroy(this.gameObject);
            }
        }

        //右から移った時
        if (Centercheck.gameObject == null && fuse_x_right.gameObject == null)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position -= new Vector3(Time.deltaTime, 0, 0);
            if (this.transform.localScale.x < 0)
            {
                Destroy(this.gameObject);
            }
        }
        //上から移った時
        else if (Centercheck.gameObject == null && fuse_z_up.gameObject == null)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position -= new Vector3(Time.deltaTime, 0, 0);
            if (this.transform.localScale.x < 0)
            {
                Destroy(gameObject);
            }
        }
        //下から移った時
        else if (Centercheck.gameObject == null && fuse_z_down.gameObject == null)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position -= new Vector3(Time.deltaTime, 0, 0);
            if(this.transform.localScale.x < 0)
            {
                Destroy(gameObject);
            }
        }
    }
}
