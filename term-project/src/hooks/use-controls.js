import { useEffect, useRef } from 'react';

const keyControlMap = {
  ArrowDown: 'backward',
  ArrowLeft: 'left',
  ArrowRight: 'right',
  ArrowUp: 'forward',
  Shift: 'brake',
};

const isKeyPressed = (v) => Object.keys(keyControlMap).includes(v);

export const useControls = () => {
  const controls = useRef({
    backward: false,
    forward: false,
    left: false,
    right: false,
    brake: false,
  });

  useEffect(() => {
    const handleKeyup = (e) =>
      isKeyPressed(e.key) && (controls.current[keyControlMap[e.key]] = false);

    const handleKeydown = (e) =>
      isKeyPressed(e.key) && (controls.current[keyControlMap[e.key]] = true);

    window.addEventListener('keyup', handleKeyup);
    window.addEventListener('keydown', handleKeydown);

    return () => {
      window.removeEventListener('keyup', handleKeyup);
      window.removeEventListener('keydown', handleKeydown);
    };
  }, []);

  return controls;
};
