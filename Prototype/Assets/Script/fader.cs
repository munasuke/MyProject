using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// FadeIn,FadeOutしたいなコード

public class fader : MonoBehaviour {
    public GameObject[] target;
    private Material[] material;

    public float alphaMax = 1.0f;
    public float alphaMin = 0.0f;

    private Color color;

    void Start()
    {
        material = new Material[target.Length];
        int cnt = 0;
        foreach(GameObject tmpTag in target)    // foreach(型 変数 in コレクション){}  コレクションのすべての要素を１回ずつ読みだす
        {
            material[cnt] = tmpTag.GetComponent<Renderer>().material;
            cnt++;
        }
        color = material[0].GetColor("_Color");
    }
}
