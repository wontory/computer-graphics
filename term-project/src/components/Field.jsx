import { Box } from '@react-three/drei';
import { RigidBody } from '@react-three/rapier';

function Field() {
  return (
    <RigidBody type="fixed" restitution={0.5}>
      <Box position={[0, 0, 0]} args={[100, 1, 100]}>
        <meshStandardMaterial color="springgreen" />
      </Box>
    </RigidBody>
  );
}

export default Field;
