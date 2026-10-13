"""Regression checks for the offline checksum reconstruction using supplied bytes."""
import unittest
from pathlib import Path
from checksum_model import calculate
class ChecksumTests(unittest.TestCase):
 def setUp(self):self.data=bytearray((Path(__file__).resolve().parents[1]/'samples'/'44.bin').read_bytes())
 def calc(self,data):return calculate(data,0x400,0xd800,0x7ffe,0x7fff,True)
 def test_supplied_image_validates(self):
  r=self.calc(self.data);self.assertEqual(r['sum'],0x5622);self.assertEqual(r['stored'],0x5622);self.assertEqual(r['residual'],0)
 def test_payload_corruption_is_detected(self):
  self.data[0x3100]+=1;self.assertEqual(self.calc(self.data)['residual'],0xffff)
 def test_stored_checksum_corruption_is_detected(self):
  self.data[0x7fff]+=1;r=self.calc(self.data);self.assertEqual(r['sum'],0x5622);self.assertEqual(r['residual'],1)
 def test_bytes_outside_configured_range_do_not_affect_result(self):
  self.data[0]=255;self.assertEqual(self.calc(self.data)['residual'],0)
if __name__=='__main__':unittest.main()
