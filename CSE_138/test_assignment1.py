################### 
# Course: CSE 138
# Quarter: Winter 2023
# Assignment: #1
# Author: Amin Karbas <mkarbasf@ucsc.edu>
###################

import unittest
import subprocess
import requests

PORT=8081
localhost = "localhost" # Docker Toolbox users should use Docker's ip address here
names = ['Slugger', 'slug', 'slg']

class TestAssignment1(unittest.TestCase):

  # Hello: basic GET request
  def test_basic_hello(self):
    res = requests.get('http://'+localhost+':'+str(PORT)+'/hello')
    self.assertEqual(res.text, 'Hello, world!', msg='Incorrect response to GET /hello endpoint')
    self.assertEqual(res.status_code, 200, msg='Did not return status 200 to GET request to /hello endpoint')

  # Hello: GET request with name query parameter
  def test_named_hello(self):
    for name in names:
      res = requests.get('http://'+localhost+':'+str(PORT)+'/hello?name='+name.strip())
      self.assertEqual(res.text, 'Hello, {}!'.format(name.strip()), msg='Incorrect response to GET /hello?name=<name> endpoint')
      self.assertEqual(res.status_code, 200, msg='Did not return status 200 to GET request to /hello endpoint')

  # Hello: POST request
  def test_post_hello(self):
    res = requests.post('http://'+localhost+':'+str(PORT)+'/hello')
    self.assertEqual(res.status_code, 405, msg='did not return status 405 to POST request to /hello endpoint')

  # Check: GET request
  def test_get_check(self):
    res = requests.get('http://'+localhost+':'+str(PORT)+'/check')
    self.assertEqual(res.text, 'All is well!', msg='Incorrect response to GET /check endpoint')
    self.assertEqual(res.status_code, 200, msg='Did not return status 200 to GET request to /check endpoint')

  # Check: POST request
  def test_post_check(self):
    res = requests.post('http://'+localhost+':'+str(PORT)+'/check')
    self.assertEqual(res.status_code, 405, msg='did not return status 405 to POST request to /check endpoint')


if __name__ == '__main__':
  unittest.main()
