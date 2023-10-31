import { useEffect } from 'react';
import { useLoader } from '@react-three/fiber';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader';
import { TextureLoader } from 'three/src/loaders/TextureLoader';

export default function Track() {
  const result = useLoader(GLTFLoader, './models/track.glb');
  const colorMap = useLoader(TextureLoader, './textures/track.png');

  const geometry = result.scene.children[0].geometry;

  useEffect(() => {
    colorMap.anisotropy = 16;
  }, [colorMap]);

  return (
    <mesh>
      <primitive object={geometry} attach="geometry" />
      <meshBasicMaterial toneMapped={false} map={colorMap} />
    </mesh>
  );
}
