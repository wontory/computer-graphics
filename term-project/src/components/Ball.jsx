import { useMemo } from 'react';
import { useLoader } from '@react-three/fiber';
import { BallCollider, RigidBody } from '@react-three/rapier';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader';

function Ball({ position }) {
  const mesh = useLoader(GLTFLoader, '/soccerball.glb').scene;

  const copiedMesh = useMemo(() => mesh.clone(), [mesh]);

  return (
    <RigidBody position={position} colliders={false} gravityScale={4}>
      <BallCollider args={[0.5]} position={[0, 1, 0]} />
      <primitive
        object={copiedMesh}
        scale={[0.54, 0.54, 0.54]}
        position={[0, 1, 0]}
      />
    </RigidBody>
  );
}

export default Ball;
