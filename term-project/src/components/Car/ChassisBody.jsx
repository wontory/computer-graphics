import { useState, Fragment } from 'react';
import { Object3D } from 'three';
import { useGLTF } from '@react-three/drei';
import chassisJeepUrl from '../../assets/car.glb?url';

const Chassis = () => {
  const { nodes, materials } = useGLTF(chassisJeepUrl);

  const [leftHeadlightTarget] = useState(() => {
    const object = new Object3D();
    object.position.set(10, -0.5, -0.7);
    return object;
  });

  const [rightHeadlightTarget] = useState(() => {
    const object = new Object3D();
    object.position.set(10, -0.5, 0.7);
    return object;
  });

  return (
    <>
      {[
        {
          position: [2.4, -0.2, -0.7],
          target: leftHeadlightTarget,
        },
        {
          position: [2.4, -0.2, 0.7],
          target: rightHeadlightTarget,
        },
      ].map(({ position, target }, idx) => (
        <Fragment key={idx}>
          <primitive object={target} />
          <spotLight
            position={position}
            target={target}
            angle={0.8}
            decay={1}
            distance={20}
            castShadow
            penumbra={1}
            intensity={10}
          ></spotLight>
        </Fragment>
      ))}
      <group position={[2.7, -2, 3.45]} rotation={[0, 1.27, 0]} dispose={null}>
        <group>
          <group position={[2.565, 1.981, -3.347]} rotation={[0, 0.295, 0]}>
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_4.geometry}
              material={materials['Material.001']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_5.geometry}
              material={materials['Material.011']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_6.geometry}
              material={materials.Basic_Glass}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_7.geometry}
              material={materials['Material.013']}
            />
          </group>
          <group position={[3.202, 2.538, -3.537]} rotation={[0, 0.295, 0]}>
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_11.geometry}
              material={materials['Material.001']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_12.geometry}
              material={materials['Material.003']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_13.geometry}
              material={materials.Basic_Glass}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_14.geometry}
              material={materials['Material.013']}
            />
          </group>
          <group
            position={[3.026, 2.053, -1.85]}
            rotation={[1.582, -0.003, -0.295]}
            scale={[0.647, 0.999, 0.089]}
          >
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_28.geometry}
              material={materials['Material.014']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_29.geometry}
              material={materials['Material.006']}
            />
          </group>
          <group position={[3.072, 3.2, -3.165]} rotation={[0, 0.295, 0]}>
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_39.geometry}
              material={materials['Material.014']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_40.geometry}
              material={materials.Material}
            />
          </group>
          <group
            position={[3.71, 2.088, -2.213]}
            rotation={[0.074, 0.295, -0.021]}
            scale={[0.035, 0.05, 0.016]}
          >
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_42.geometry}
              material={materials['Material.014']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_43.geometry}
              material={materials.Material}
            />
          </group>
          <group
            position={[2.506, 1.777, -5.347]}
            rotation={[0, -1.275, -Math.PI / 2]}
            scale={[0.366, 1, 1]}
          >
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_60.geometry}
              material={materials['Material.014']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_61.geometry}
              material={materials['Material.016']}
            />
          </group>
          <group
            position={[1.581, 2.084, -5.185]}
            rotation={[0, 0.295, 0]}
            scale={0.223}
          >
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_67.geometry}
              material={materials['Material.007']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_68.geometry}
              material={materials['Material.005']}
            />
          </group>
          <group
            position={[2.222, 2.276, -5.379]}
            rotation={[-0.239, -1.267, 1.343]}
            scale={0.376}
          >
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_76.geometry}
              material={materials['Material.005']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_77.geometry}
              material={materials['Material.004']}
            />
          </group>
          <group
            position={[3.105, 2.283, -3.147]}
            rotation={[0, 0.295, 0]}
            scale={[0.16, 0.16, 0.057]}
          >
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_81.geometry}
              material={materials['Material.014']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_82.geometry}
              material={materials['Material.012']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_83.geometry}
              material={materials['Material.003']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_84.geometry}
              material={materials['Material.008']}
            />
          </group>
          <group
            position={[2.772, 2.688, -3.915]}
            rotation={[0, 0.295, 0]}
            scale={[0.116, 0.075, 0.046]}
          >
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_96.geometry}
              material={materials['Material.010']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_97.geometry}
              material={materials['Material.002']}
            />
          </group>
          <group
            position={[2.046, 2.688, -3.695]}
            rotation={[0, 0.295, 0]}
            scale={[0.104, 0.075, 0.046]}
          >
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_99.geometry}
              material={materials['Material.010']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_100.geometry}
              material={materials['Material.002']}
            />
          </group>
          <group position={[2.565, 1.981, -3.347]} rotation={[0, 0.295, 0]}>
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_108.geometry}
              material={materials['Material.009']}
            />
            <mesh
              castShadow
              receiveShadow
              geometry={nodes.Object_109.geometry}
              material={materials['Material.005']}
            />
          </group>
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_9.geometry}
            material={materials['Material.001']}
            position={[2.843, 2.277, -2.434]}
            rotation={[0.009, 0.295, -0.003]}
            scale={[0.251, 0.1, 0.434]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_16.geometry}
            material={materials['Material.015']}
            position={[3.716, 2.016, -4.641]}
            rotation={[0, 0.295, 0]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_18.geometry}
            material={materials['Material.015']}
            position={[3.411, 1.576, -3.6]}
            rotation={[0, 0.295, 0]}
            scale={0.207}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_20.geometry}
            material={materials['Material.003']}
            position={[3.408, 2.093, -2.889]}
            rotation={[0.045, 0.339, -0.669]}
            scale={[0.015, 0.104, 0.069]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_22.geometry}
            material={materials['Material.003']}
            position={[3.304, 1.841, -3.24]}
            rotation={[0.074, 0.295, -0.021]}
            scale={[0.02, 0.045, 0.141]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_24.geometry}
            material={materials['Material.014']}
            position={[3.294, 2.289, -3.269]}
            rotation={[0.074, 0.295, -0.021]}
            scale={0.042}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_26.geometry}
            material={materials['Material.014']}
            position={[3.449, 2.516, -3.305]}
            rotation={[1.638, -0.021, -0.538]}
            scale={[0.086, 0.071, 0.07]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_31.geometry}
            material={materials['Material.014']}
            position={[3.017, 2.124, -1.868]}
            rotation={[0.343, 0.279, -0.098]}
            scale={[0.283, 1, 0.034]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_33.geometry}
            material={materials.Material}
            position={[3.55, 2.053, -2.013]}
            rotation={[1.59, -0.006, -0.295]}
            scale={[0.074, 0.05, 0.074]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_35.geometry}
            material={materials.Material}
            position={[3.379, 2.053, -1.961]}
            rotation={[1.59, -0.006, -0.295]}
            scale={[0.064, 0.043, 0.064]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_37.geometry}
            material={materials['Material.014']}
            position={[3.02, 2.282, -1.858]}
            rotation={[0.343, 0.279, -0.098]}
            scale={[0.326, 1, 0.034]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_45.geometry}
            material={materials['Material.004']}
            position={[3.134, 1.898, -1.493]}
            rotation={[1.638, -0.021, 1.276]}
            scale={[0.035, 0.051, 0.035]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_47.geometry}
            material={materials['Material.002']}
            position={[3.049, 1.742, -1.763]}
            rotation={[0, 0.295, 0]}
            scale={[0.819, 1, 0.082]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_49.geometry}
            material={materials['Material.014']}
            position={[2.569, 1.981, -3.349]}
            rotation={[-3.068, -0.295, -3.12]}
            scale={[0.431, 1, 1]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_63.geometry}
            material={materials['Material.003']}
            position={[1.735, 1.633, -4.999]}
            rotation={[Math.PI / 2, 0, -0.295]}
            scale={[0.032, 0.027, 0.027]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_65.geometry}
            material={materials['Material.012']}
            position={[3.206, 1.459, -2.549]}
            rotation={[0, 0.295, 0]}
            scale={[-0.042, 0.508, 0.412]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_70.geometry}
            material={materials['Material.005']}
            position={[1.588, 2.084, -5.178]}
            rotation={[0, 0.295, 0]}
            scale={[0.183, 0.234, 0.141]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_72.geometry}
            material={materials['Material.017']}
            position={[2.91, 2.036, -4.097]}
            rotation={[0, 0.295, 0]}
            scale={0.648}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_74.geometry}
            material={materials['Material.006']}
            position={[1.684, 2.45, -5.337]}
            rotation={[0, 0.295, 0]}
            scale={[0.135, 0.105, 0.139]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_79.geometry}
            material={materials['Material.005']}
            position={[2.222, 2.276, -5.379]}
            rotation={[-0.239, -1.267, 1.343]}
            scale={0.376}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_86.geometry}
            material={materials['Material.002']}
            position={[3.048, 2.291, -3.316]}
            rotation={[-1.571, 0, 0.295]}
            scale={[-0.025, 0.025, 0.025]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_88.geometry}
            material={materials['Material.006']}
            position={[2.907, 1.767, -3.079]}
            rotation={[-1.099, 0.137, 0.262]}
            scale={[0.059, 0.044, 0.059]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_90.geometry}
            material={materials['Material.006']}
            position={[3.037, 1.767, -3.14]}
            rotation={[-1.383, 0.057, 0.29]}
            scale={[0.059, 0.044, 0.059]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_92.geometry}
            material={materials['Material.012']}
            position={[3.05, 2.291, -3.309]}
            rotation={[Math.PI / 2, 0, -0.295]}
            scale={0.135}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_94.geometry}
            material={materials['Material.012']}
            position={[2.269, 2.298, -3.017]}
            rotation={[Math.PI / 2, 0, 2.846]}
            scale={[0.108, 0.131, 0.139]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_102.geometry}
            material={materials['Material.002']}
            position={[2.586, 1.412, -4.634]}
            rotation={[0, 0.295, 0]}
            scale={[-0.042, 0.508, 0.412]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_104.geometry}
            material={materials['Material.006']}
            position={[2.612, 1.945, -3.214]}
            rotation={[-0.667, 0.235, 0.181]}
            scale={0.019}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_106.geometry}
            material={materials['Material.009']}
            position={[2.574, 2.119, -3.337]}
            rotation={[Math.PI / 2, 0, -1.866]}
            scale={0.029}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_111.geometry}
            material={materials['Material.006']}
            position={[3.316, 2.465, -3.26]}
            rotation={[2.779, 1.248, 1.987]}
            scale={0.114}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_113.geometry}
            material={materials['Material.006']}
            position={[3.312, 1.539, -2.365]}
            rotation={[3.121, 0.845, -3.126]}
            scale={[0.071, 0.105, 0.071]}
          />
          <mesh
            castShadow
            receiveShadow
            geometry={nodes.Object_115.geometry}
            material={materials['Material.006']}
            position={[2.66, 1.539, -4.484]}
            rotation={[3.121, 0.845, -3.126]}
            scale={[0.071, 0.11, 0.071]}
          />
        </group>
      </group>
    </>
  );
};

export default Chassis;
