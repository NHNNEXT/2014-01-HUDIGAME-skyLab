xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Cube {
    FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 1.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Cube mesh
      24;
      -31.759651;-31.759651;31.759651;,
      -31.759651;-31.759651;-31.759651;,
      -31.759651;31.759651;-31.759651;,
      -31.759651;31.759651;31.759651;,
      -31.759651;31.759651;31.759651;,
      -31.759651;31.759651;-31.759651;,
      31.759651;31.759651;-31.759651;,
      31.759651;31.759651;31.759651;,
      31.759651;31.759651;31.759651;,
      31.759651;31.759651;-31.759651;,
      31.759651;-31.759651;-31.759651;,
      31.759651;-31.759651;31.759651;,
      31.759651;-31.759651;31.759651;,
      31.759651;-31.759651;-31.759651;,
      -31.759651;-31.759651;-31.759651;,
      -31.759651;-31.759651;31.759651;,
      -31.759651;-31.759651;-31.759651;,
      31.759651;-31.759651;-31.759651;,
      31.759651;31.759651;-31.759651;,
      -31.759651;31.759651;-31.759651;,
      31.759651;-31.759651;31.759651;,
      -31.759651;-31.759651;31.759651;,
      -31.759651;31.759651;31.759651;,
      31.759651;31.759651;31.759651;;
      6;
      4;0,1,2,3;,
      4;4,5,6,7;,
      4;8,9,10,11;,
      4;12,13,14,15;,
      4;16,17,18,19;,
      4;20,21,22,23;;
      MeshNormals { // Cube normals
        6;
         1.000000; 0.000000; 0.000000;,
        -0.000000;-1.000000; 0.000000;,
        -1.000000; 0.000000; 0.000000;,
        -0.000000; 1.000000; 0.000000;,
         0.000000; 0.000000; 1.000000;,
         0.000000;-0.000000;-1.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Cube normals
      MeshTextureCoords { // Cube UV coordinates
        24;
         0.999913; 0.335078;,
         0.999913; 0.667302;,
         0.749957; 0.667302;,
         0.749957; 0.335078;,
         0.749957; 0.335078;,
         0.749957; 0.667302;,
         0.500000; 0.667302;,
         0.500000; 0.335078;,
         0.500000; 0.335078;,
         0.500000; 0.667302;,
         0.251207; 0.667302;,
         0.250043; 0.335078;,
         0.250043; 0.335078;,
         0.251207; 0.667302;,
         0.000087; 0.667302;,
         0.000087; 0.335078;,
         0.251207; 1.002630;,
         0.251207; 0.667302;,
         0.500000; 0.667302;,
         0.500000; 1.002630;,
         0.250043; 0.335078;,
         0.250043; 0.001834;,
         0.500000; 0.001834;,
         0.500000; 0.335078;;
      } // End of Cube UV coordinates
      MeshMaterialList { // Cube material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;;
        Material Sky {
           0.640000; 0.640000; 0.640000; 1.000000;;
           96.078431;
           0.500000; 0.500000; 0.500000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"stormydays_large.jpg";}
        }
      } // End of Cube material list
    } // End of Cube mesh
  } // End of Cube
} // End of Root