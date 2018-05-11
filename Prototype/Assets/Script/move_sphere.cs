using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class move_sphere : MonoBehaviour {
    private Vector3 nowPos = Vector3.zero;
    Vector3 vec = Vector3.zero;
	void Start () {
	}
	
	public void OnUserAction () {
        //nowPos = this.transform.position;//現座標の取得

        //下
        vec = new Vector3(0, 0, -1);
        if (CheckMove(vec) == false)
        {
            transform.position += new Vector3(0, 0, -10);
        }
        Debug.DrawRay(transform.position, vec, Color.red);

        //    //上
        vec = new Vector3(0, 0, 1);
        if (CheckMove(vec) == false)
        {
            transform.position += new Vector3(0, 0, 10);
        }

        //    //左
        //    vec = new Vector3(1, 0, 0);
        //    if (CheckMove(vec) == false)
        //    {
        //        transform.position += new Vector3(10, 0, 0);
        //    }

        //    //右
        //    vec = new Vector3(-1, 0, 0);
        //    if (CheckMove(vec) == false)
        //    {
        //        transform.position += new Vector3(-10, 0, 0);
        //    }
    }

    bool CheckMove(Vector3 dir) {
        if (Physics.Raycast(transform.position, dir, 5.0f) == true) {
            return true;
        }
        return false;
    }
}
