import { useMemo } from 'react';
import { useLoader } from '@react-three/fiber';
import { CuboidCollider, RigidBody } from '@react-three/rapier';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader';

function CrateBox({ position }) {
  const mesh = useLoader(GLTFLoader, '/crate_box.glb').scene;

  const copiedMesh = useMemo(() => mesh.clone(), [mesh]);

  return (
    <RigidBody position={position} colliders={false} gravityScale={1}>
      <CuboidCollider args={[0.4, 0.4, 0.4]} position={[0, 1, 0]} />
      <primitive
        object={copiedMesh}
        position={[0, 0.7, 0]}
        scale={[0.35, 0.35, 0.35]}
      />
    </RigidBody>
  );
}

export default CrateBox;
