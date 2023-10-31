import { useEffect, useRef } from 'react';
import { BufferAttribute, CircleGeometry, Mesh } from 'three';
import { useLoader } from '@react-three/fiber';
import { TextureLoader } from 'three/src/loaders/TextureLoader';
import { MeshReflectorMaterial } from '@react-three/drei';

export default function Ground() {
  const meshRef = useRef(null);
  const meshRef2 = useRef(null);

  const gridMap = useLoader(TextureLoader, './textures/grid.png');
  const aoMap = useLoader(TextureLoader, './textures/ground-ao.png');
  const alphaMap = useLoader(TextureLoader, './textures/alpha-map.png');

  useEffect(() => {
    gridMap.anisotropy = 16;
  }, [gridMap]);

  useEffect(() => {
    const uvs = meshRef.current.geometry.attributes.uv.array;
    meshRef.current.geometry.setAttribute('uv2', new BufferAttribute(uvs, 2));

    const uvs2 = meshRef2.current.geometry.attributes.uv.array;
    meshRef2.current.geometry.setAttribute('uv2', new BufferAttribute(uvs2, 2));
  }, [meshRef.current, meshRef2.current]);

  return (
    <>
      <mesh
        position={[-2.285, -0.01, -1.325]}
        rotation-x={-Math.PI * 0.5}
        ref={meshRef2}
      >
        <planeGeometry args={[12, 12]} />
        <meshBasicMaterial
          opacity={0.325}
          alphaMap={gridMap}
          transparent={true}
          color={'white'}
        />
      </mesh>
      <mesh
        position={[-2.285, -0.015, -1.325]}
        rotation-x={-Math.PI * 0.5}
        rotation-z={-0.079}
        ref={meshRef}
      >
        <circleGeometry args={[6.12, 50]} />
        <MeshReflectorMaterial
          alphaMap={alphaMap}
          aoMap={aoMap}
          transparent={true}
          color={[0.5, 0.5, 0.5]}
          envMapIntensity={0.35}
          metalness={0.05}
          roughness={0.4}
          dithering={true}
          blur={[1024, 512]}
          mixBlur={3}
          mixStrength={30}
          mixContrast={1}
          resolution={1024}
          mirror={0}
          depthScale={0}
          minDepthThreshold={0.9}
          maxDepthThreshold={1}
          depthToBlurRatioBias={0.25}
          debug={0}
          reflectorOffset={0.02}
        />
      </mesh>
    </>
  );
}
