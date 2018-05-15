using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PanelControl : MonoBehaviour {
    public Transform PanelPrefab;
    public Transform topPanel;//０番
    public int divisionNum;//分割数

    public Material material;
    Color[] itemColor = { Color.clear, Color.red, Color.blue, Color.green, Color.yellow, Color.magenta };

    void Start () {
        //配置場所の設定
        Vector3 panelPos = new Vector3(
            topPanel.position.x - topPanel.localScale.x/2 + PanelPrefab.localScale.x/2, 
            0, 
            topPanel.position.z - topPanel.localScale.z/2 - PanelPrefab.localScale.z/2);

        //回転角の設定
        Quaternion q = new Quaternion();
        q = Quaternion.identity;
        //幅と奥行きの設定
        Vector3 localScale = PanelPrefab.localScale;
        localScale.x = topPanel.localScale.x / divisionNum;
        PanelPrefab.localScale = localScale;

        for (int i = 0; i < divisionNum; i++) {
            Transform panel = Instantiate(PanelPrefab, panelPos, q);
            panelPos.x += (panel.transform.localScale.x * 10);
            //Materialの設定
            Renderer r = panel.GetComponent<Renderer>();
            r.material.color = itemColor[0];
        }
    }
	
	void Update () {
	}
}
