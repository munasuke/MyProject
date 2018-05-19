using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class fuse_z_down : MonoBehaviour
{
    public GameObject fusecheck;
    public GameObject fusecheck2;

    public GameObject fuse_x_right;
    public GameObject fuse_x_left;
    public GameObject fuse_z_up;
   
    public GameObject Centercheck;

    private bool FuseFlag = false;
    private bool FuseFlag2 = false;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        FuseFlag = fusecheck.GetComponent<tip_Manager>().fuseFlag;
        FuseFlag2 = fusecheck2.GetComponent<tip_Manager2>().fuseFlag2;

        //下から当たると下から消えだす
        if (FuseFlag)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position -= new Vector3(0, 0, Time.deltaTime);
            if (this.transform.localScale.x < 0)
            {
                Destroy(this.gameObject);
            }
        }

        //上から当たると上から消えだす
        if (FuseFlag2)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position += new Vector3(0, 0, Time.deltaTime);
            if (this.transform.localScale.x < 0)
            {
                Destroy(this.gameObject);
            }
        }

        //上から移った時
        if (Centercheck.gameObject == null && fuse_z_up.gameObject == null)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position -= new Vector3(0, 0, Time.deltaTime);
            if (this.transform.localScale.x < 0)
            {
                Destroy(this.gameObject);
            }
        }
        //右から移った時
        else if(Centercheck.gameObject == null && fuse_x_right.gameObject == null)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position -= new Vector3(0, 0, Time.deltaTime);
            if (this.transform.localScale.x < 0)
            {
                Destroy(this.gameObject);
            }
        }
        //左から移った時
        else if(Centercheck.gameObject == null && fuse_x_left.gameObject == null)
        {
            this.transform.localScale -= new Vector3(Time.deltaTime * 2, 0, 0);
            this.transform.position -= new Vector3(0, 0, Time.deltaTime);
            if (this.transform.localScale.x < 0)
            {
                Destroy(this.gameObject);
            }
        }
    }
}