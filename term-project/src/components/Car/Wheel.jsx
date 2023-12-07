import { useRef } from 'react';
import { useGLTF } from '@react-three/drei';
import wheelGlbUrl from '../../assets/wheel-draco.glb?url';

const Wheel = ({ side, radius, ...props }) => {
  const groupRef = useRef(null);

  const { nodes, materials } = useGLTF(wheelGlbUrl);
  const scale = radius / 0.34;

  return (
    <group dispose={null} {...props} ref={groupRef}>
      <group scale={scale}>
        <group scale={side === 'left' ? -1 : 1}>
          <mesh
            castShadow
            geometry={nodes.Mesh_14.geometry}
            material={materials['Material.002']}
          />
          <mesh
            castShadow
            geometry={nodes.Mesh_14_1.geometry}
            material={materials['Material.009']}
          />
        </group>
      </group>
    </group>
  );
};

export default Wheel;
