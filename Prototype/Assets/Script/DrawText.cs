using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DrawText : MonoBehaviour {
    void OnGUI() {
        GUI.Label(new Rect(210, 215, 150, 100), "StartPanel");
        GUI.Label(new Rect(850, 300, 150, 100), "GoalPanel");
    }
}
