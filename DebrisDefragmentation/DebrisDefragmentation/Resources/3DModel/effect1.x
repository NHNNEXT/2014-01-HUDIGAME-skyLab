xof 0303txt 0032

template XSkinMeshHeader {
  <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
  WORD nMaxSkinWeightsPerVertex;
  WORD nMaxSkinWeightsPerFace;
  WORD nBones;
}

template SkinWeights {
  <6f0d123b-bad2-4167-a0d0-80224f25fabb>
  STRING transformNodeName;
  DWORD nWeights;
  array DWORD vertexIndices[nWeights];
  array float weights[nWeights];
  Matrix4x4 matrixOffset;
}

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Plane_001 {
    FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 1.000000, 0.000000,
       0.052538,-0.001602, 1.001667, 1.000000;;
    }
    Mesh { // Plane_001 mesh
      4;
      -1.000000;-1.000000; 0.000000;,
       1.000000;-1.000000; 0.000000;,
       1.000000; 1.000000; 0.000000;,
      -1.000000; 1.000000; 0.000000;;
      1;
      4;0,1,2,3;;
      MeshNormals { // Plane_001 normals
        1;
        -0.000000;-0.000000;-1.000000;;
        1;
        4;0,0,0,0;;
      } // End of Plane_001 normals
      MeshTextureCoords { // Plane_001 UV coordinates
        4;
         0.000100; 0.999900;,
         0.999900; 0.999900;,
         0.999900; 0.000100;,
         0.000100; 0.000100;;
      } // End of Plane_001 UV coordinates
      MeshMaterialList { // Plane_001 material list
        1;
        1;
        0;;
        Material Material_001 {
           0.640000; 0.640000; 0.640000; 1.000000;;
           96.078431;
           0.500000; 0.500000; 0.500000;;
           0.000000; 0.000000; 0.000000;;
	TextureFilename {"effect1.png";}
        }
      } // End of Plane_001 material list
    } // End of Plane_001 mesh
  } // End of Plane_001
} // End of Root
