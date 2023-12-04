import { useRef } from 'react';
import { useFrame } from '@react-three/fiber';
import { Sphere, useKeyboardControls } from '@react-three/drei';
import { BallCollider, RigidBody } from '@react-three/rapier';

function Car() {
  const car = useRef();

  const leftPressed = useKeyboardControls((state) => state['left']);
  const rightPressed = useKeyboardControls((state) => state['right']);
  const backPressed = useKeyboardControls((state) => state['back']);
  const forwardPressed = useKeyboardControls((state) => state['forward']);

  const handleMovement = () => {
    if (rightPressed) car.current.applyImpulse({ x: 0.1, y: 0, z: 0 });
    if (leftPressed) car.current.applyImpulse({ x: -0.1, y: 0, z: 0 });
    if (backPressed) car.current.applyImpulse({ x: 0, y: 0, z: 0.1 });
    if (forwardPressed) car.current.applyImpulse({ x: 0, y: 0, z: -0.1 });
  };

  useFrame(() => {
    handleMovement();
  });

  return (
    <RigidBody
      position={[0, 5, 0]}
      colliders={false}
      gravityScale={4}
      ref={car}
    >
      <BallCollider args={[1]} position={[0, 1, 0]} />
      <Sphere position-y={1}>
        <meshStandardMaterial color={'hotpink'} />
      </Sphere>
    </RigidBody>
  );
}

export default Car;
